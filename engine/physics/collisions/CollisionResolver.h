#ifndef ENGINE_PHYSICS_COLLISIONS_RESOLVER
#define ENGINE_PHYSICS_COLLISIONS_RESOLVER

#include <vector>
#include <unordered_set>
#include "engine/drawables/GameObject.h"
#include "engine/physics/collisions/CollisionDetector.h"

class CollisionResolver {
public:
	CollisionResolver() = default;
	CollisionResolver(CollisionDetector&);
	/// <summary>
	/// Nudge game object o1 away from o2 until they are no longer intersecting.
	/// </summary>
	void separateObjects(GameObject& o1, std::vector<GameObject>&) const;
	void addObjectForSeparation(ID id);
	bool shouldSeparate(ID id);
private:
	const float resolutionSpeed = 0.99f; // The speed we move game objects away from one another so they no longer intersect.
	CollisionDetector detector;
	std::unordered_set<ID> objectsToSeparate;
};

#endif // !ENGINE_PHYSICS_COLLISIONS_RESOLVER
