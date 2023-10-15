#include "CollisionResolver.h"

#include <iostream>

#include "engine/physics/collisions/CollisionData.h"
#include "engine/physics/collisions/CollisionDetector.h"

CollisionResolver::CollisionResolver(CollisionDetector& detector): detector(detector)
{
}

void CollisionResolver::separateObjects(GameObject& o1, std::vector<GameObject>& objs) const
{
	// Save the previous direction and speed because we will set them after the resolution has been completed.
	float o1Speed = o1.speed;
	Direction o1Dir = o1.direction;
	Vec2 o1DirVec = o1Dir.getWorldSpace();

	if ((o1DirVec.x == 0.0f && o1DirVec.y == 0.0f) || o1Speed == 0.0f) {
		return;
	}

	// While separating the objects use smaller steps
	o1.setSpeed(resolutionSpeed);
	// Go backwards from where it came. Reverse time to unstuck the objects
	o1.steer(-o1Dir.getWorldSpace());

	while (detector.checkCollisions(o1, objs)) {
		o1.updatePosition();
	}

	o1.setSpeed(o1Speed);
	o1.steer(o1Dir.getWorldSpace());
}
