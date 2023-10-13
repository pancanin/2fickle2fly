#ifndef ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H
#define ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H

#include <vector>
#include <functional>

#include "engine/drawables/GameObject.h"

typedef std::function<void(const GameObject&, const GameObject&)> CollisionCallback;

class CollisionDetector {
public:
	void checkCollisions(const std::vector<GameObject>&, CollisionCallback) const;
};

#endif // !ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H
