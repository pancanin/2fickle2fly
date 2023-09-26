#ifndef ENGINE_COLLISIONS_SEGMENTER_H
#define ENGINE_COLLISIONS_SEGMENTER_H

#include <vector>
#include <cstdint>

#include "BoundingBox.h"
#include "engine/math/Vec2.h"

struct Rect;

/// <summary>
/// Shapes are constructed from segments. This allows for resolving the normal at the collision location.
/// For example, a rectangle is constructed out of 4 segments, one for each side.
/// When a collision occurs, the colliding segments can be found and their normal will be known.
/// </summary>
struct Segment {
	BoundingBox bb;
	Vec2 N;
};

class Segmenter {
public:
	Segmenter(uint32_t segmentThickness) : segmentThickness(segmentThickness) {}
	/// <summary>
	/// Returns 4 bounding boxes, 1 for each side of the rectangle.
	/// The order is the following: top, right, bottom, left segment.
	/// Uses a predefined thickness for the resulting bounding boxes.
	/// They should be thin enough, as not to be larger than the rectangle itself.
	/// Note: Does not work well with really small/thin rectangles.
	/// </summary>
	std::vector<Segment> segment(const Rect& r) const; // TODO: Change this to a Segment structure with BoundingBox + normal
private:
	/// <summary>
	/// For the segments created for the purposes of collision detection, and more specifically, for the purpose of checking
	/// which side of the boxes/rectangles has collided.
	/// For horizontal segments this value will represent the height of the segment.
	/// For vertical, this value is the width of a segment.
	/// </summary>
	uint32_t segmentThickness;
};

#endif // !ENGINE_COLLISIONS_SEGMENTER_H
