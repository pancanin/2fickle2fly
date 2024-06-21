#include <gtest/gtest.h>

#include "engine/math/Vec2.h"
#include "engine/drawables/GameObject.h"

// Demonstrate some basic assertions.
TEST(Vec2Test, BasicAdd) {
  Vec2 a(1.0, 0.0);
  Vec2 b(0.0, 1.0);
  Vec2 c = a + b;
  ASSERT_EQ(c.x, 1.0);
  ASSERT_EQ(c.y, 1.0);
}

TEST(Vec2Test, AddCommutativeProperty) {
  Vec2 a(1.0, 0.0);
  Vec2 b(0.0, 1.0);
  Vec2 c = a + b;
  Vec2 d = b + a;
  ASSERT_EQ(c.x, d.x);
  ASSERT_EQ(c.y, d.y);
}

TEST(Vec2Test, MultiplyBasic) {
  Vec2 a(2.0, 3.0);
  float scale = 2;
  Vec2 b = a * scale;
  ASSERT_EQ(b.x, 4.0);
  ASSERT_EQ(b.y, 6.0);
}

TEST(Vec2Test, ReflectBasic1) {
  Vec2 a(1.0, 1.0);
  Vec2 b = a.reflect(Vec2(0, -1));
  ASSERT_EQ(b.x, 1.0);
  ASSERT_EQ(b.y, -1.0);
}

TEST(Vec2Test, ReflectBasic2) {
  Vec2 a(1.0, 1.0);
  Vec2 b = a.reflect(Vec2(-1, 0));
  ASSERT_EQ(b.x, -1.0);
  ASSERT_EQ(b.y, 1.0);
}

TEST(Vec2Test, ReflectVertical) {
  Vec2 a(0, 1);
  Vec2 b = a.reflect(Vec2(0, -1));
  ASSERT_EQ(b.x, 0.0);
  ASSERT_EQ(b.y, -1.0);
}

TEST(Vec2Test, ReflectGameObject) {
  GameObject obj = GameObjectFactory::createObject(Vec2(), 10, 20, Color{}, 4.5);
  obj.setDirection(Vec2(0, 1));
  //Vec2 b = obj.direction.getWorldSpace().reflect(Vec2(0, -1));
  //ASSERT_EQ(b.x, 0.0);
  //ASSERT_EQ(b.y, -1.0);
}

