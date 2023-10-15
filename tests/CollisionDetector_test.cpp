#include <gtest/gtest.h>

#include <vector>
#include <iostream>

#include "engine/drawables/GameObject.h"
#include "engine/physics/collisions/Segmenter.h"

#include "engine/physics/collisions/CollisionDetector.h"

TEST(CollisionDetectorTest, CollisionBetweenTwoObjectsWithOneTouchingSide) {

	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(20, 10), 5, 10, Color{});
	GameObject o2 = GameObjectFactory::createImmovableObject(Vec2(10, 18), 20, 10, Color{});
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	std::vector<GameObject> objs{ o1, o2 };
	CollisionDetector detector;

	bool hasCollision = false;
	detector.checkCollisions(objs, [&hasCollision](const GameObject& o1, const GameObject& o2) {
		hasCollision = true;
	});
	ASSERT_TRUE(hasCollision);
}

TEST(CollisionDetectorTest, CollisionBetweenTwoObjectsWithOneTouchingCorners) {

	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(0, 0), 20, 10, Color{});
	GameObject o2 = GameObjectFactory::createImmovableObject(Vec2(18, 8), 20, 10, Color{});
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	std::vector<GameObject> objs{ o1, o2 };
	CollisionDetector detector;

	bool hasCollision = false;
	detector.checkCollisions(objs, [&hasCollision](const GameObject& o1, const GameObject& o2) {
		hasCollision = true;
		});
	ASSERT_TRUE(hasCollision);
}

TEST(CollisionDetectorTest, CollisionBetweenTwoObjectsFoundBug) {

	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(264, 448), 128, 32, Color{});
	GameObject o2 = GameObjectFactory::createImmovableObject(Vec2(320, 420), 16, 16, Color{});
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	std::vector<GameObject> objs{ o1, o2 };
	Segmenter seg(3);
	CollisionDetector detector;

	bool hasCollision = false;
	detector.checkCollisions(objs, [&hasCollision](const GameObject& o1, const GameObject& o2) {
		hasCollision = true;
		});
	ASSERT_FALSE(hasCollision);
}

TEST(CollisionDetectorTest, SixSideCollisions) {

	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(0, 0), 10, 8, Color{});
	GameObject o2 = GameObjectFactory::createImmovableObject(Vec2(8, 0), 10, 8, Color{});
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	std::vector<GameObject> objs{ o1, o2 };
	CollisionDetector detector;

	bool hasCollision = false;
	detector.checkCollisions(objs, [&hasCollision](const GameObject& o1, const GameObject& o2) {
		hasCollision = true;
	});
	ASSERT_TRUE(hasCollision);
}

TEST(CollisionDetectorTest, OddCaseWhichShouldNotCollide) {

	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(200, 16.89f), 10, 10, Color{});
	GameObject o2 = GameObjectFactory::createImmovableObject(Vec2(206, 0), 32, 16, Color{});
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	std::vector<GameObject> objs{ o1, o2 };
	CollisionDetector detector;

	bool hasCollision = false;
	detector.checkCollisions(objs, [&hasCollision](const GameObject& o1, const GameObject& o2) {
		hasCollision = true;
	});
	ASSERT_FALSE(hasCollision);
}

TEST(CollisionDetectorTest, OddCaseWhichShouldNotCollide2) {

	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(200.51, 16.69f), 10, 10, Color{});
	GameObject o2 = GameObjectFactory::createImmovableObject(Vec2(206, 0), 32, 16, Color{});
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	std::vector<GameObject> objs{ o1, o2 };
	CollisionDetector detector;

	bool hasCollision = false;
	detector.checkCollisions(objs, [&hasCollision](const GameObject& o1, const GameObject& o2) {
		hasCollision = true;
		});
	ASSERT_FALSE(hasCollision);
}
