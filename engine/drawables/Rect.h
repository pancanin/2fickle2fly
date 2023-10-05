#ifndef ENGINE_DRAWABLES_RECT_H
#define ENGINE_DRAWABLES_RECT_H

#include <vector>

#include "engine/drawables/Color.h"
#include "engine/math/Vec2.h"

struct Rect {

	Rect() = default;

	float getX() const {
		return x;
	}

	float getY() const {
		return y;
	}

	float getWidth() const {
		return w;
	}

	float getHeight() const {
		return h;
	}

	Color getColor() const {
		return color;
	}

	std::vector<Vec2> getNormals() const {
		return { top, right, bottom, left };
	}

	void updatePosition(const Vec2& newPos) {
		this->x = newPos.x;
		this->y = newPos.y;
	}

	Rect toWorldSpace() {
		Rect r = *this;
		r.y = -r.y;
		return r;
	}

	struct Factory {
		// Creates a rect that has normals on all its sides, so it can collide with objects from any direction.
		static Rect createStandardRect(float x, float y, float w, float h, const Color& c) {
			return Rect(Vec2(0, 1), Vec2(1, 0), Vec2(0, -1), Vec2(-1, 0), x, y, w, h, c);
		}

		static Rect createCustomNormalsRect(const Vec2& topSegment, const Vec2& rightSegment, const Vec2& bottomSegment, const Vec2& leftSegment, float x, float y, float w, float h, const Color& c) {
			return Rect(topSegment, rightSegment, bottomSegment, leftSegment, x, y, w, h, c);
		}
	};

	friend struct Rect::Factory;
private:
	Rect(const Vec2& topSegment, const Vec2& rightSegment, const Vec2& bottomSegment, const Vec2& leftSegment, float x, float y, float w, float h, const Color& c)
		: top(topSegment), right(rightSegment), bottom(bottomSegment), left(leftSegment), x(x), y(y), w(w), h(h), color(c) {}

	Vec2 top; // Top segment
	Vec2 right; // Right segment
	Vec2 bottom; // Bottom segment
	Vec2 left; // Left segment
	float x, y, w, h;
	Color color;
};

#endif // !ENGINE_DRAWABLES_RECT_H
