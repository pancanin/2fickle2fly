#ifndef ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H
#define ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H

#include <cstdint>
#include <vector>

#include "engine/math/Vec2.h"
#include "engine/drawables/GameObject.h"
#include "engine/physics/collisions/Segmenter.h"

/// <summary>
/// Collisions between objects.
/// </summary>
struct CollisionData {
	CollisionData(ID o1Id, ID o2Id, const Vec2& o1N, const Vec2& o2N) : o1Id(o1Id), o2Id(o2Id), o1N(o1N), o2N(o2N), hasCollision(true) {}
	CollisionData() : o1Id(-1), o2Id(-1), o1N(Vec2()), o2N(Vec2()), hasCollision(false) {}
	ID o1Id; /// The id of one of the collided objects. We name it object 1 (o1), but the order should not matter.
	ID o2Id; /// Id of 'object 2'.
	Vec2 o1N; /// Normal of the 'first' object.
	Vec2 o2N; /// Normal of the 'second' object.
	bool hasCollision;
};

class CollisionDetector {
public:
	CollisionDetector(const Segmenter&);
	/// <summary>
	/// Returns information about collisions between segments.
	/// Does not stop after the first detected collision and so returns a vector of collisions for the current frame.
	/// This will allow for resolving multiple concurrent collision events.
	/// The results will be ordered with the collisions of the GameObjects in the beginning of the collection first.
	/// So it is expected that in CollisionData, element with 'o1Id' will always be to the left of element with o2Id.
	/// The segments will be compared in the order which comes from Segmenter.
	/// </summary>
	std::vector<CollisionData> checkCollisions(const std::vector<GameObject>&) const;

	// Thoughts:
	// No matter what strategy I use for the segments, there always will be multiple colliding segments.
	// I should research ways to do this without segments but with code and rects, but that can be even harder.
	// So, there should be a way to compact multiple collisions between the same objects and have a smooth normal of the collision.
private:
	Segmenter segmenter;
};

#endif // !ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H
