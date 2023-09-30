#include "Segmenter.h"

#include "engine/drawables/Rect.h"

std::vector<Segment> Segmenter::segment(const Rect& r) const
{
	std::vector<Segment> segments;
	float x = r.getX();
	float y = r.getY();
	float w = r.getWidth();
	float h = r.getHeight();
	float t = segmentThickness;
	std::vector<Vec2> normals = r.getNormals();

	segments.push_back(Segment{ BoundingBox(Vec2(x, y - t), Vec2(x + w, y)), normals[0] });
	segments.push_back(Segment{ BoundingBox(Vec2(x + w - t, y - h), Vec2(x + w, y)), normals[1] });
	segments.push_back(Segment{ BoundingBox(Vec2(x, y - h), Vec2(x + w, y - h + t)), normals[2] });
	segments.push_back(Segment{ BoundingBox(Vec2(x, y - h), Vec2(x + t, y)), normals[3] });

	return segments;
}
