#include <gtest/gtest.h>

#include <vector>

#include "engine/drawables/GameObject.h"
#include "engine/physics/collisions/Segmenter.h"

#include "engine/physics/collisions/CollisionDetector.h"

TEST(CollisionDetectorTest, CollisionBetweenTwoObjectsWithOneTouchingSide) {

	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(20, -10), 5, 10, Color{});
	GameObject o2 = GameObjectFactory::createImmovableObject(Vec2(10, -18), 20, 10, Color{});
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	std::vector<GameObject> objs{ o1, o2 };
	Segmenter seg(5);
	CollisionDetector detector(seg);

	std::vector<CollisionData> collisions = detector.checkCollisions(objs);

	// We expect 3 collisions
	ASSERT_EQ(collisions.size(), 3);
	ASSERT_TRUE(collisions[0].hasCollision);
	ASSERT_TRUE(collisions[1].hasCollision);
	ASSERT_TRUE(collisions[2].hasCollision);

	ASSERT_EQ(collisions[0].o1Id, o1Id);
	ASSERT_EQ(collisions[0].o2Id, o2Id);
	ASSERT_EQ(collisions[1].o1Id, o1Id);
	ASSERT_EQ(collisions[1].o2Id, o2Id);
	ASSERT_EQ(collisions[2].o1Id, o1Id);
	ASSERT_EQ(collisions[2].o2Id, o2Id);

	ASSERT_EQ(collisions[0].o1N.x, 1);
	ASSERT_EQ(collisions[0].o1N.y, 0);
	ASSERT_EQ(collisions[0].o2N.x, 0);
	ASSERT_EQ(collisions[0].o2N.y, 1);

	ASSERT_EQ(collisions[1].o1N.x, 0);
	ASSERT_EQ(collisions[1].o1N.y, -1);
	ASSERT_EQ(collisions[1].o2N.x, 0);
	ASSERT_EQ(collisions[1].o2N.y, 1);

	ASSERT_EQ(collisions[2].o1N.x, -1);
	ASSERT_EQ(collisions[2].o1N.y, 0);
	ASSERT_EQ(collisions[2].o2N.x, 0);
	ASSERT_EQ(collisions[2].o2N.y, 1);
}

TEST(CollisionDetectorTest, CollisionBetweenTwoObjectsWithOneTouchingCorners) {

	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(0, 0), 20, 10, Color{});
	GameObject o2 = GameObjectFactory::createImmovableObject(Vec2(18, 8), 20, 10, Color{});
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	std::vector<GameObject> objs{ o1, o2 };
	Segmenter seg(3);
	CollisionDetector detector(seg);

	std::vector<CollisionData> collisions = detector.checkCollisions(objs);

	// We expect 4 collisions
	ASSERT_EQ(collisions.size(), 4);
	ASSERT_TRUE(collisions[0].hasCollision);
	ASSERT_TRUE(collisions[1].hasCollision);
	ASSERT_TRUE(collisions[2].hasCollision);
	ASSERT_TRUE(collisions[3].hasCollision);

	ASSERT_EQ(collisions[0].o1Id, o1Id);
	ASSERT_EQ(collisions[0].o2Id, o2Id);
	ASSERT_EQ(collisions[1].o1Id, o1Id);
	ASSERT_EQ(collisions[1].o2Id, o2Id);
	ASSERT_EQ(collisions[2].o1Id, o1Id);
	ASSERT_EQ(collisions[2].o2Id, o2Id);
	ASSERT_EQ(collisions[3].o1Id, o1Id);
	ASSERT_EQ(collisions[3].o2Id, o2Id);

	ASSERT_EQ(collisions[0].o1N.x, 1);
	ASSERT_EQ(collisions[0].o1N.y, 0);
	ASSERT_EQ(collisions[0].o2N.x, 0);
	ASSERT_EQ(collisions[0].o2N.y, 1);

	ASSERT_EQ(collisions[1].o1N.x, 1);
	ASSERT_EQ(collisions[1].o1N.y, 0);
	ASSERT_EQ(collisions[1].o2N.x, -1);
	ASSERT_EQ(collisions[1].o2N.y, 0);

	ASSERT_EQ(collisions[2].o1N.x, 0);
	ASSERT_EQ(collisions[2].o1N.y, -1);
	ASSERT_EQ(collisions[2].o2N.x, 0);
	ASSERT_EQ(collisions[2].o2N.y, 1);

	ASSERT_EQ(collisions[3].o1N.x, 0);
	ASSERT_EQ(collisions[3].o1N.y, -1);
	ASSERT_EQ(collisions[3].o2N.x, -1);
	ASSERT_EQ(collisions[3].o2N.y, 0);
}

TEST(CollisionDetectorTest, CollisionBetweenTwoObjectsFoundBug) {

	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(264, 448), 128, 32, Color{});
	GameObject o2 = GameObjectFactory::createImmovableObject(Vec2(320, 420), 16, 16, Color{});
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	std::vector<GameObject> objs{ o1, o2 };
	Segmenter seg(3);
	CollisionDetector detector(seg);

	std::vector<CollisionData> collisions = detector.checkCollisions(objs);

	//ASSERT_EQ(collisions.size(), 0);
}