#ifndef ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H
#define ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H

#include <vector>
#include <functional>

#include "engine/drawables/GameObject.h"

typedef std::function<void(GameObject&, GameObject&)> CollisionCallback;

class CollisionDetector {
public:
	void checkCollisions(std::vector<GameObject>&, CollisionCallback) const;
	bool checkCollisions(GameObject&, std::vector<GameObject>&) const;
};

#endif // !ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H
