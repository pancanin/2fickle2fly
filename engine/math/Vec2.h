#ifndef ENGINE_MATH_VEC2_H
#define ENGINE_MATH_VEC2_H

#include <cstdint>
#include <math.h>

class Vec2 {
public:
	Vec2() : x(0.0f), y(0.0f) {}
	Vec2(float x, float y): x(x), y(y) {}

	const Vec2 operator+(const Vec2& b) const {
		return Vec2(x + b.x, y + b.y);
	}

	const Vec2 operator*(float s) const {
		return Vec2(x * s, y * s);
	}

	/// <summary>
	/// Returns a copy of the current instance, but normalized.
	/// </summary>
	Vec2 normalized() const {
		return *this * (1 / length());
	}

	float length() const {
		return sqrtf(x * x + y * y);
	}

	float x;
	float y;
};

#endif // !ENGINE_MATH_VEC2_H
