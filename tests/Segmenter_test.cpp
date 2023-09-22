#include <gtest/gtest.h>

#include <vector>

#include "engine/physics/collisions/Segmenter.h"
#include "engine/drawables/Rect.h"

TEST(SegmenterTest, GenerateFourSegmentsSpanningFourQuadrants) {
	uint32_t thickness = 5;
	Segmenter s(thickness);
	Rect r(-10, 10, 50, 40, Color{});

	std::vector<BoundingBox> segments = s.segment(r);
	ASSERT_EQ(segments[0].min.x, -10);
	ASSERT_EQ(segments[0].min.y, 5);
	ASSERT_EQ(segments[0].max.x, 40);
	ASSERT_EQ(segments[0].max.y, 10);

	ASSERT_EQ(segments[1].min.x, 35);
	ASSERT_EQ(segments[1].min.y, -30);
	ASSERT_EQ(segments[1].max.x, 40);
	ASSERT_EQ(segments[1].max.y, 10);

	ASSERT_EQ(segments[2].min.x, -10);
	ASSERT_EQ(segments[2].min.y, -30);
	ASSERT_EQ(segments[2].max.x, 40);
	ASSERT_EQ(segments[2].max.y, -25);

	ASSERT_EQ(segments[3].min.x, -10);
	ASSERT_EQ(segments[3].min.y, -30);
	ASSERT_EQ(segments[3].max.x, -5);
	ASSERT_EQ(segments[3].max.y, 10);
}