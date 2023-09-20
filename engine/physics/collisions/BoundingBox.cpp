#include "BoundingBox.h"

bool BoundingBox::intersects(const BoundingBox& other) const
{
	return this->max.x > other.min.x && other.max.x > this->min.x &&
		this->max.y > other.min.y && other.max.y > this->min.y;
}
