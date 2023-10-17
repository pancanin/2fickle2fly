#ifndef ENGINE_DRAWABLES_RECT_H
#define ENGINE_DRAWABLES_RECT_H

#include "engine/drawables/Color.h"
#include "engine/math/Vec2.h"
#include "engine/physics/collisions/BoundingBox.h"

struct Rect {
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

	void updatePosition(const Vec2& newPos) {
		this->x = newPos.x;
		this->y = newPos.y;
		BoundingBox bb = calcBB();
		this->bb.min = bb.min;
		this->bb.max = bb.max;
	}

	Rect toWorldSpace() const {
		Rect r = *this;
		r.y = -r.y;
		return r;
	}

	const BoundingBox& toBoundingBox() const {
		return bb;
	}

	struct Factory {
		static Rect createRect(float x, float y, float w, float h, const Color& c) {
			return Rect(x, y, w, h, c);
		}
	};

	friend struct Rect::Factory;
private:
	Rect(float x, float y, float w, float h, const Color& c): x(x), y(y), w(w), h(h), color(c), bb(calcBB()) {}

	float x, y, w, h;
	Color color;
	BoundingBox bb;

	BoundingBox calcBB() {
		return BoundingBox(Vec2(x, -y - h), Vec2(x + w, -y));
	}
};

#endif // !ENGINE_DRAWABLES_RECT_H
