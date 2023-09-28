#ifndef ENGINE_PHYSICS_COLLISIONS_COLLISION_DATA
#define ENGINE_PHYSICS_COLLISIONS_COLLISION_DATA

#include "engine/misc/ID.h"
#include "engine/math/Vec2.h"

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

	/// <summary>
	/// Checks whether the current collision involves an object with the provided id.
	/// If it does, it returns a new instance, so that the queried object's normal and id are set to o1Id and o1N.
	/// The other collided object is set to o2Id and o2N.
	/// This helps look for objects which we want to manipulate and extract their collision data.
	/// </summary>
	/// <param name="id">The id of the object which we want to check for collisions.</param>
	/// <returns>A new CollisionData instance with the, potentially, swapped fields or an 'empty' CollisionData object when there are no collisions with this object.</returns>
	CollisionData query(ID id) const;
};

#endif // !ENGINE_PHYSICS_COLLISIONS_COLLISION_DATA
