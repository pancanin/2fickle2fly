#ifndef ENGINE_PHYSICS_COLLISIONS_COLLISIONAGGREGATOR
#define ENGINE_PHYSICS_COLLISIONS_COLLISIONAGGREGATOR

#include <vector>

#include "engine/physics/collisions/CollisionData.h"

class CollisionAggregator {
public:
	/// <summary>
	/// Important Note!!!
	/// Currently we will support only 1-to-1 collisions between objects. This was an accident, due to bad design :D
	/// 
	/// Collects information about collisions and averages it for an object.
	/// Each object is constructed from segments. If there are multiple segments colliding, this method will average the collision data, so it applies to the whole object.
	/// For example, if there are 2 colliding segments from each rectangle, this method will average the normals to simulate a hit on the corner and then
	/// one of the objects may have a diagonal trajectory as a result.
	/// Or when resolving collisions of a ball to a wall, we need the normal of the wall exactly from the side where the ball hit so we can reflect the ball appropriately.
	/// </summary>
	/// <param name="collisions">Collisions per segment of an object</param>
	/// <returns>Collision data for the colliding objects. The collision data will always be for the same two objects and their order will be the same in each collision object.</returns>
	CollisionData aggregateCollisions(std::vector<CollisionData>& collisions) const;
};

#endif // !ENGINE_PHYSICS_COLLISIONS_COLLISIONAGGREGATOR