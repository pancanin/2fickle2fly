#include <gtest/gtest.h>

#include <vector>

#include "engine/math/Vec2.h"
#include "engine/physics/collisions/CollisionData.h"
#include "engine/physics/collisions/CollisionAggregator.h"

TEST(CollisionAggregatorTest, FindHitNormalOfObjectAboveAndBelow) {
	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(0, 0), 5, 5, Color{});
	GameObject o2 = GameObjectFactory::createImmovableObject(Vec2(0, 10), 10, 10, Color{});
	CollisionAggregator aggr;
	Vec2 n = aggr.calculateHitNormal(o1, o2);

	ASSERT_EQ(n.x, 0);
	ASSERT_EQ(n.y, -1);

	n = aggr.calculateHitNormal(o2, o1);

	ASSERT_EQ(n.x, 0);
	ASSERT_EQ(n.y, 1);
}

TEST(CollisionAggregatorTest, FindHitNormalOfObjectSideways) {
	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(0, 0), 5, 5, Color{});
	GameObject o2 = GameObjectFactory::createImmovableObject(Vec2(10, 0), 10, 10, Color{});
	CollisionAggregator aggr;
	Vec2 n = aggr.calculateHitNormal(o1, o2);

	ASSERT_EQ(n.x, 1);
	ASSERT_EQ(n.y, 0);

	n = aggr.calculateHitNormal(o2, o1);

	ASSERT_EQ(n.x, -1);
	ASSERT_EQ(n.y, 0);
}
