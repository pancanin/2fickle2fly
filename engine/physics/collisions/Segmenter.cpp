#include "Segmenter.h"

#include "engine/drawables/Rect.h"

std::vector<Segment> Segmenter::segment(const Rect& r) const
{
	std::vector<Segment> segments;
	auto rect = r._rect;
	auto t = segmentThickness;

	segments.push_back(Segment{ BoundingBox(Vec2(rect.x, rect.y - t), Vec2(rect.x + rect.w, rect.y)), Vec2(0, 1) });
	segments.push_back(Segment{ BoundingBox(Vec2(rect.x + rect.w - t, rect.y - rect.h), Vec2(rect.x + rect.w, rect.y)), Vec2(1, 0) });
	segments.push_back(Segment{ BoundingBox(Vec2(rect.x, rect.y - rect.h), Vec2(rect.x + rect.w, rect.y - rect.h + t)), Vec2(0, -1) });
	segments.push_back(Segment{ BoundingBox(Vec2(rect.x, rect.y - rect.h), Vec2(rect.x + t, rect.y)), Vec2(-1, 0) });

	return segments;
}
