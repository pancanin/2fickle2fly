#include "CollisionAggregator.h"

#include <utility>
#include <unordered_map>
#include <iostream>

#include "engine/physics/collisions/CollisionData.h"
#include "engine/misc/ID.h"

// Represents a pair of objects that have collided.
typedef std::pair<ID, ID> CollisionKey;

struct Hash {
	std::size_t operator()(const CollisionKey& r) const {
		std::size_t res = 17;
		res = res * 31 + std::hash<ID>()(r.first);
		res = res * 31 + std::hash<ID>()(r.second);
		return res;
	}
};

typedef std::unordered_map<CollisionKey, CollisionData, Hash> CollisionAggregate;

std::vector<CollisionData> CollisionAggregator::aggregateCollisions(std::vector<CollisionData>& collisions) const
{
	CollisionAggregate collisionAggregate;

	for (CollisionData& collision : collisions) {
		CollisionKey key = std::make_pair(collision.o1Id, collision.o2Id);

		if (collisionAggregate.find(key) != collisionAggregate.end()) {
			// We already have an existing record for this collision, so lets accumulate the normals.
			CollisionData c = collisionAggregate[key];

			c.o1N = c.o1N + collision.o1N;
			c.o2N = c.o2N + collision.o2N;
			collisionAggregate[key] = c;
		}
		else {
			CollisionData c(collision.o1Id, collision.o2Id, collision.o1N, collision.o2N);
			collisionAggregate[key] = c;
		}
	}

	std::vector<CollisionData> aggrCollisions;

	for (auto& c : collisionAggregate) {
		c.second.o1N = c.second.o1N.normalized();
		c.second.o2N = c.second.o2N.normalized();
		aggrCollisions.push_back(c.second);
		std::cout << "Found a collision between objects with id: " << c.second.o1Id <<
			" and id: " << c.second.o2Id << '\n';
	}

	return aggrCollisions;
}

std::vector<CollisionData> CollisionAggregator::getFirstCollision(std::vector<CollisionData>& collisions) const
{
	return std::vector<CollisionData>();
}
