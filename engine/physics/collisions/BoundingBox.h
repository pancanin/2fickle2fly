#ifndef ENGINEV2_COLLISIONS_BOUNDING_BOX_H
#define ENGINEV2_COLLISIONS_BOUNDING_BOX_H

#include "engine/math/Vec2.h"

class BoundingBox {
public:
	BoundingBox() : min(Vec2()), max(Vec2()) {}
	BoundingBox(Vec2 min, Vec2 max) : min(min), max(max) {}

	bool intersects(const BoundingBox& other) const;

	Vec2 min;
	Vec2 max;
};

#endif // !ENGINEV2_COLLISIONS_BOUNDING_BOX_H
