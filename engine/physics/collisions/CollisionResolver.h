#ifndef ENGINE_PHYSICS_COLLISIONS_RESOLVER
#define ENGINE_PHYSICS_COLLISIONS_RESOLVER

#include "engine/drawables/GameObject.h"

class CollisionDetector;

class CollisionResolver {
public:
	CollisionResolver(CollisionDetector&);
	/// <summary>
	/// Nudge game object o1 away from o2 until they are no longer intersecting.
	/// </summary>
	void separateObjects(GameObject& o1, GameObject& o2) const;

private:
	const float resolutionSpeed = 0.7f; // The speed we move game objects away from one another so they no longer intersect.
	CollisionDetector& detector;
};

#endif // !ENGINE_PHYSICS_COLLISIONS_RESOLVER
