#include <gtest/gtest.h>

#include <vector>

#include "engine/physics/collisions/Segmenter.h"
#include "engine/drawables/Rect.h"

TEST(SegmenterTest, GenerateFourSegmentsSpanningFourQuadrants) {
	uint32_t thickness = 5;
	Segmenter s(thickness);
	Rect r(-10, 10, 50, 40, Color{});

	std::vector<Segment> segments = s.segment(r);
	ASSERT_EQ(segments[0].bb.min.x, -10);
	ASSERT_EQ(segments[0].bb.min.y, 5);
	ASSERT_EQ(segments[0].bb.max.x, 40);
	ASSERT_EQ(segments[0].bb.max.y, 10);
	ASSERT_EQ(segments[0].N.x, 0);
	ASSERT_EQ(segments[0].N.y, 1);

	ASSERT_EQ(segments[1].bb.min.x, 35);
	ASSERT_EQ(segments[1].bb.min.y, -30);
	ASSERT_EQ(segments[1].bb.max.x, 40);
	ASSERT_EQ(segments[1].bb.max.y, 10);
	ASSERT_EQ(segments[1].N.x, 1);
	ASSERT_EQ(segments[1].N.y, 0);

	ASSERT_EQ(segments[2].bb.min.x, -10);
	ASSERT_EQ(segments[2].bb.min.y, -30);
	ASSERT_EQ(segments[2].bb.max.x, 40);
	ASSERT_EQ(segments[2].bb.max.y, -25);
	ASSERT_EQ(segments[2].N.x, 0);
	ASSERT_EQ(segments[2].N.y, -1);

	ASSERT_EQ(segments[3].bb.min.x, -10);
	ASSERT_EQ(segments[3].bb.min.y, -30);
	ASSERT_EQ(segments[3].bb.max.x, -5);
	ASSERT_EQ(segments[3].bb.max.y, 10);
	ASSERT_EQ(segments[3].N.x, -1);
	ASSERT_EQ(segments[3].N.y, 0);
}