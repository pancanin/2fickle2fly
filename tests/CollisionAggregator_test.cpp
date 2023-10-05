#include <gtest/gtest.h>

#include <vector>

#include "engine/math/Vec2.h"
#include "engine/physics/collisions/CollisionData.h"
#include "engine/physics/collisions/CollisionAggregator.h"

TEST(CollisionAggregatorTest, CompactCollisionDataPerObject) {
	std::vector<CollisionData> collisions{
		CollisionData(1, 2, Vec2(1, 0), Vec2(0, 1)),
		CollisionData(1, 2, Vec2(0, -1), Vec2(0, 1)),
		CollisionData(1, 2, Vec2(-1, 0), Vec2(0, 1))
	};
	CollisionAggregator colAggr;

	std::vector<CollisionData> aggrcollisions = colAggr.aggregateCollisions(collisions);

	ASSERT_TRUE(aggrcollisions[0].hasCollision);
	ASSERT_EQ(aggrcollisions[0].o1Id, 1);
	ASSERT_EQ(aggrcollisions[0].o2Id, 2);

	ASSERT_EQ(aggrcollisions[0].o1N.x, 0);
	ASSERT_EQ(aggrcollisions[0].o1N.y, -1);
	ASSERT_EQ(aggrcollisions[0].o2N.x, 0);
	ASSERT_EQ(aggrcollisions[0].o2N.y, 1);
}

TEST(CollisionAggregatorTest, CompactCollisionDataPerObjectAtCorner) {
	std::vector<CollisionData> collisions{
		CollisionData(1, 2, Vec2(1, 0), Vec2(0, 1)),
		CollisionData(1, 2, Vec2(1, 0), Vec2(-1, 0)),
		CollisionData(1, 2, Vec2(0, -1), Vec2(0, 1)),
		CollisionData(1, 2, Vec2(0, -1), Vec2(-1, 0))
	};
	CollisionAggregator colAggr;

	std::vector<CollisionData> aggrcollisions = colAggr.aggregateCollisions(collisions);

	ASSERT_TRUE(aggrcollisions[0].hasCollision);
	ASSERT_EQ(aggrcollisions[0].o1Id, 1);
	ASSERT_EQ(aggrcollisions[0].o2Id, 2);

	ASSERT_FLOAT_EQ(aggrcollisions[0].o1N.x, 0.707107f);
	ASSERT_FLOAT_EQ(aggrcollisions[0].o1N.y, -0.707107f);
	ASSERT_FLOAT_EQ(aggrcollisions[0].o2N.x, -0.707107f);
	ASSERT_FLOAT_EQ(aggrcollisions[0].o2N.y, 0.707107f);
}
