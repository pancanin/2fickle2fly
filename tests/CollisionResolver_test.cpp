#include <gtest/gtest.h>

#include "engine/physics/collisions/CollisionResolver.h"
#include "engine/physics/collisions/CollisionDetector.h"
#include "engine/drawables/GameObject.h"

TEST(CollisionResolverTest, SeparatingTwoObjectsHittingOnEdge) {
	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(0, 0), 20, 10);
	GameObject o2 = GameObjectFactory::createObject(Vec2(18, 8), 20, 10, Color{}, 4.0f, Vec2(-1, -1));
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	CollisionDetector detector;
	CollisionResolver r(detector);
	std::vector<GameObject> objs = { o1, o2 };
	bool colliding = false;
	detector.checkCollisions(objs, [&colliding](const GameObject& o1, const GameObject& o2) {
		colliding = true;
	});

	ASSERT_TRUE(colliding);

	r.separateObjects(objs[1], objs);

	colliding = false;
	detector.checkCollisions(objs, [&colliding](const GameObject& o1, const GameObject& o2) {
		colliding = true;
	});

	ASSERT_FALSE(colliding);
}

TEST(CollisionResolverTest, SeparatingTwoObjectsHittingSideways) {
	GameObject o1 = GameObjectFactory::createImmovableObject(Vec2(0, 0), 20, 10);
	GameObject o2 = GameObjectFactory::createObject(Vec2(5, 5), 10, 10, Color{}, 4.0f, Vec2(0, 1));
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	CollisionDetector detector;
	CollisionResolver r(detector);
	std::vector<GameObject> objs = { o1, o2 };
	bool colliding = false;
	detector.checkCollisions(objs, [&colliding](const GameObject& o1, const GameObject& o2) {
		colliding = true;
	});
	ASSERT_TRUE(colliding);
	r.separateObjects(objs[1], objs);

	colliding = false;
	detector.checkCollisions(objs, [&colliding](const GameObject& o1, const GameObject& o2) {
		colliding = true;
		});

	ASSERT_FALSE(colliding);
}

TEST(CollisionResolverTest, SeparatingTwoMovingObjectsHitting) {
	GameObject o1 = GameObjectFactory::createObject(Vec2(0, 0), 10, 10, Color{}, 4.0f, Vec2(1, -1));
	GameObject o2 = GameObjectFactory::createObject(Vec2(5, 5), 15, 15, Color{}, 4.0f, Vec2(-1, 1));
	ID o1Id = o1.getId();
	ID o2Id = o2.getId();
	CollisionDetector detector;
	CollisionResolver r(detector);
	std::vector<GameObject> objs = { o1, o2 };
	bool colliding = false;
	detector.checkCollisions(objs, [&colliding](const GameObject& o1, const GameObject& o2) {
		colliding = true;
		});
	ASSERT_TRUE(colliding);
	r.separateObjects(objs[0], objs);

	colliding = false;
	detector.checkCollisions(objs, [&colliding](const GameObject& o1, const GameObject& o2) {
		colliding = true;
		});

	ASSERT_FALSE(colliding);
}
