#include <gtest/gtest.h>

#include "engine/physics/collisions/BoundingBox.h"

TEST(BoundingBoxTest, UpperLeftPartIntersection) {
  BoundingBox a(Vec2(0.0, 0.0), Vec2(2.0, 2.0));
  BoundingBox b(Vec2(1.0, 1.0), Vec2(3.0, 3.0));
  ASSERT_TRUE(b.intersects(a));
  ASSERT_TRUE(a.intersects(b));
}

TEST(BoundingBoxTest, LowerLeftPartIntersection) {
  BoundingBox a(Vec2(0.0, 0.0), Vec2(2.0, 2.0));
  BoundingBox b(Vec2(1.0, -1.0), Vec2(3.0, 1.0));
  ASSERT_TRUE(b.intersects(a));
  ASSERT_TRUE(a.intersects(b));
}

TEST(BoundingBoxTest, LowerRightPartIntersection) {
  BoundingBox a(Vec2(0.0, 0.0), Vec2(2.0, 2.0));
  BoundingBox b(Vec2(-1.0, -1.0), Vec2(1.0, 1.0));
  ASSERT_TRUE(b.intersects(a));
  ASSERT_TRUE(a.intersects(b));
}

TEST(BoundingBoxTest, UpperRightPartIntersection) {
  BoundingBox a(Vec2(0.0, 0.0), Vec2(2.0, 2.0));
  BoundingBox b(Vec2(-1.0, 1.0), Vec2(1.0, 3.0));
  ASSERT_TRUE(b.intersects(a));
  ASSERT_TRUE(a.intersects(b));
}

TEST(BoundingBoxTest, Nested) {
  BoundingBox a(Vec2(0.0, 0.0), Vec2(2.0, 2.0));
  BoundingBox b(Vec2(-1.0, -1.0), Vec2(3.0, 3.0));
  ASSERT_TRUE(a.intersects(b));
  ASSERT_TRUE(b.intersects(a));
}

TEST(BoundingBoxTest, Neighbouring) {
  BoundingBox a(Vec2(0.0, 0.0), Vec2(2.0, 2.0));
  BoundingBox b(Vec2(0.0, -2.0), Vec2(2.0, 0.0));
  ASSERT_FALSE(a.intersects(b));
  ASSERT_FALSE(b.intersects(a));
}

TEST(BoundingBoxTest, TestN1) {
  BoundingBox a(Vec2(0.0, 10.0), Vec2(20.0, 7.0));
  BoundingBox b(Vec2(18.0, 11.0), Vec2(38.0, 8.0));
  ASSERT_FALSE(a.intersects(b));
  ASSERT_FALSE(b.intersects(a));
}

