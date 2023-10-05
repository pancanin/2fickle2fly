#include "CollisionResolver.h"

#include "engine/physics/collisions/CollisionData.h"
#include "engine/physics/collisions/CollisionDetector.h"

CollisionResolver::CollisionResolver(CollisionDetector& detector): detector(detector)
{
}

void CollisionResolver::separateObjects(GameObject& o1, GameObject& o2) const
{
	while (true) {
		auto collision = detector.checkCollisions({ o1, o2 });

		// Objects are unstuck
		if (collision.empty()) {
			break;
		}

		float oldSpeed = o1.speed;
		o1.setSpeed(resolutionSpeed);
		o1.updatePosition();
		o1.setSpeed(oldSpeed);
	}
}
