#include "CollisionAggregator.h"

CollisionData CollisionAggregator::aggregateCollisions(std::vector<CollisionData>& collisions) const
{
	CollisionData aggrCollision;

	for (CollisionData& collision : collisions) {

		// There is no issue in reassigning these each time because they should be the same.
		aggrCollision.o1Id = collision.o1Id;
		aggrCollision.o2Id = collision.o2Id;
		aggrCollision.hasCollision = collision.hasCollision;

		aggrCollision.o1N = aggrCollision.o1N + collision.o1N;
		aggrCollision.o2N = aggrCollision.o2N + collision.o2N;
	}

	aggrCollision.o1N = aggrCollision.o1N.normalized();
	aggrCollision.o2N = aggrCollision.o2N.normalized();

	return aggrCollision;
}
