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
	}

	Rect toWorldSpace() const {
		Rect r = *this;
		r.y = -r.y;
		return r;
	}

	BoundingBox toBoundingBox() const {
		return BoundingBox(Vec2(x, y), Vec2(x + w, y + h));
	}

	struct Factory {
		static Rect createRect(float x, float y, float w, float h, const Color& c) {
			return Rect(x, y, w, h, c);
		}
	};

	friend struct Rect::Factory;
private:
	Rect(float x, float y, float w, float h, const Color& c): x(x), y(y), w(w), h(h), color(c) {}

	float x, y, w, h;
	Color color;
};

#endif // !ENGINE_DRAWABLES_RECT_H
