#ifndef ENGINE_MATH_VEC2_H
#define ENGINE_MATH_VEC2_H

#include <cstdint>

class Vec2 {
public:
	Vec2() : x(0.0f), y(0.0f) {}
	Vec2(float x, float y): x(x), y(y) {}

	Vec2 operator+(const Vec2& b) const {
		return Vec2(x + b.x, y + b.y);
	}

	Vec2 operator*(float s) const {
		return Vec2(x * s, y * s);
	}

	float x;
	float y;
};

#endif // !ENGINE_MATH_VEC2_H
