#include "CollisionResolver.h"

#include <iostream>

#include "engine/physics/collisions/CollisionData.h"
#include "engine/physics/collisions/CollisionDetector.h"

CollisionResolver::CollisionResolver(CollisionDetector& detector): detector(detector)
{
}

void CollisionResolver::separateObjects(GameObject& o1, GameObject& o2, const Vec2& prevBallDir) const
{
	std::cout << "Object (" << o1.getId() << "): with direction (" <<
		o1.direction.getWorldSpace().x << ", " << o1.direction.getWorldSpace().y << ")" <<
		" and position: (" << o1.rect.getX() << ", " << o1.rect.getY() << ")\n";
	std::cout << "Object (" << o2.getId() << "): with direction (" <<
		o2.direction.getWorldSpace().x << ", " << o2.direction.getWorldSpace().y << ")" <<
	" and position: (" << o1.rect.getX() << ", " << o1.rect.getY() << ")\n";

	// Save the previous direction and speed because we will set them after the resolution has been completed.
	float oldSpeed = o1.speed;
	Direction oldDir = o1.direction;
	
	// While separating the objects use smaller steps
	o1.setSpeed(resolutionSpeed);

	// Go backwards from where it came. Reverse time to unstuck the objects
	o1.steer(-prevBallDir);

	auto collision = detector.checkCollisions({ o1, o2 });
	while (!collision.empty()) {
		std::cout << "Unstucking objects" << std::endl;
		o1.updatePosition();
		collision = detector.checkCollisions({ o1, o2 });
	}

	o1.setSpeed(oldSpeed);
	o1.steer(oldDir.getWorldSpace());
}
