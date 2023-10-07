#include "CollisionResolver.h"

#include <iostream>

#include "engine/physics/collisions/CollisionData.h"
#include "engine/physics/collisions/CollisionDetector.h"

CollisionResolver::CollisionResolver(CollisionDetector& detector): detector(detector)
{
}

void CollisionResolver::separateObjects(GameObject& o1, GameObject& o2) const
{
	std::cout << "Object (" << o1.getId() << "): with direction (" <<
		o1.direction.getWorldSpace().x << ", " << o1.direction.getWorldSpace().y << ")" <<
		" and position: (" << o1.rect.getX() << ", " << o1.rect.getY() << ')\n';
	std::cout << "Object (" << o2.getId() << "): with direction (" <<
		o2.direction.getWorldSpace().x << ", " << o2.direction.getWorldSpace().y << ")" <<
	" and position: (" << o1.rect.getX() << ", " << o1.rect.getY() << ')\n';
	while (true) {
		auto collision = detector.checkCollisions({ o1, o2 });

		// Objects are unstuck
		if (collision.empty()) {
			std::cout << "THe objects are not stuck anymore" << '\n';
			break;
		}

		std::cout << "Unstucking objects" << std::endl;

		float oldSpeed = o1.speed;
		o1.setSpeed(resolutionSpeed);
		o1.updatePosition();
		o1.setSpeed(oldSpeed);
	}
}
