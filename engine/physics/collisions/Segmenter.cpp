#include "Segmenter.h"

#include "engine/drawables/Rect.h"

std::vector<BoundingBox> Segmenter::segment(const Rect& r) const
{
	std::vector<BoundingBox> segments;

	auto& rect = r._rect;
	auto t = segmentThickness;

	segments.push_back(BoundingBox(Vec2(rect.x, rect.y - t), Vec2(rect.x + rect.w, rect.y)));
	segments.push_back(BoundingBox(Vec2(rect.x + rect.w - t, rect.y - rect.h), Vec2(rect.x + rect.w, rect.y)));
	segments.push_back(BoundingBox(Vec2(rect.x, rect.y - rect.h), Vec2(rect.x + rect.w, rect.y - rect.h + t)));
	segments.push_back(BoundingBox(Vec2(rect.x, rect.y - rect.h), Vec2(rect.x + t, rect.y)));

	return segments;
}
