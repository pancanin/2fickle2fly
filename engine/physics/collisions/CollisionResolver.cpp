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
		" and position: (" << o1.rect.getX() << ", " << o1.rect.getY() << ")\n";
	std::cout << "Object (" << o2.getId() << "): with direction (" <<
		o2.direction.getWorldSpace().x << ", " << o2.direction.getWorldSpace().y << ")" <<
	" and position: (" << o2.rect.getX() << ", " << o2.rect.getY() << ")\n";

	// Save the previous direction and speed because we will set them after the resolution has been completed.
	float o1Speed = o1.speed;
	Direction o1Dir = o1.direction;
	float o2Speed = o2.speed;
	Direction o2Dir = o2.direction;
	
	// While separating the objects use smaller steps
	o1.setSpeed(resolutionSpeed);
	o2.setSpeed(resolutionSpeed);
	// Go backwards from where it came. Reverse time to unstuck the objects
	o1.steer(-o1Dir.getWorldSpace());
	o2.steer(-o2Dir.getWorldSpace());

	while (true) {
		bool exit = true;
		detector.checkCollisions({ o1, o2 }, [&exit](const GameObject& o1, const GameObject& o2) {
			exit = false;
		});
		if (exit) { break; }
		std::cout << "Unstucking objects, so obj 1 has (x: " << o1.rect.getX() << ", y: " << o1.rect.getY() << ") and obj 2 has (x: " <<
		 o2.rect.getX() << ", y: " << o2.rect.getY() << ")" << std::endl;
		o1.updatePosition();
		o2.updatePosition();
	}

	o1.setSpeed(o1Speed);
	o1.steer(o1Dir.getWorldSpace());
	o2.setSpeed(o2Speed);
	o2.steer(o2Dir.getWorldSpace());
}
