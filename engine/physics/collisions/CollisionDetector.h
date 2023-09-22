#ifndef ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H
#define ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H

#include <cstdint>
#include <vector>

#include "engine/math/Vec2.h"
#include "engine/drawables/GameObject.h"

struct CollisionData {
	CollisionData(int32_t o1Id, int32_t o2Id, const Vec2& o1N, const Vec2& o2N) : o1Id(o1Id), o2Id(o2Id), o1N(o1N), o2N(o2N), hasCollision(true) {}
	CollisionData() : o1Id(-1), o2Id(-1), o1N(Vec2()), o2N(Vec2()), hasCollision(false) {}
	int32_t o1Id; /// The id of one of the collided objects. We name it object 1 (o1), but the order should not matter.
	int32_t o2Id; /// Id of 'object 2'.
	Vec2 o1N; /// Normal of the 'first' object.
	Vec2 o2N; /// Normal of the 'second' object.
	bool hasCollision;
};

class CollisionDetector {
public:
	/// <summary>
	/// Does not stop after the first detected collision and so returns a vector of collisions for the current frame.
	/// This will allow for resolving multiple concurrent collision events.
	/// </summary>
	std::vector<CollisionData> checkCollisions(const std::vector<GameObject>&) const;
};

#endif // !ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H
