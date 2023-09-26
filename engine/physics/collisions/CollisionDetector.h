#ifndef ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H
#define ENGINE_PHYSICS_COLLISIONS_COLLISION_DETECTOR_H

#include <cstdint>
#include <vector>

#include "engine/math/Vec2.h"
#include "engine/drawables/GameObject.h"
#include "engine/physics/collisions/Segmenter.h"
#include "engine/physics/collisions/CollisionData.h"

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
	/// 
	/// Big Note: Does not handle nested objects
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
