#ifndef ENGINE_COLLISIONS_SEGMENTER_H
#define ENGINE_COLLISIONS_SEGMENTER_H

#include <vector>
#include <cstdint>

#include "BoundingBox.h"

struct Rect;

class Segmenter {
public:
	Segmenter(uint32_t segmentThickness) : segmentThickness(segmentThickness) {}
	/// <summary>
	/// Returns 4 bounding boxes, 1 for each side of the rectangle.
	/// Uses a predefined thickness for the resulting bounding boxes.
	/// They should be thin enough, as not to be larger than the rectangle itself.
	/// Note: Does not work well with really small/thin rectangles.
	/// </summary>
	std::vector<BoundingBox> segmentize(const Rect& r) const;
private:
	/// <summary>
	/// For the segments created for the purposes of collision detection, and more specifically, for the purpose of checking
	/// which side of the boxes/rectangles has collided.
	/// For horizontal segments this value will represent the height of the segment.
	/// For vertical, this value is the width of a segment.
	/// </summary>
	uint32_t segmentThickness = 5;
};

#endif // !ENGINE_COLLISIONS_SEGMENTER_H
