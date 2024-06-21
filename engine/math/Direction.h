#ifndef ENGINE_MATH_DIRECTION_H
#define ENGINE_MATH_DIRECTION_H

#include "engine/math/Vec2.h"


/// <summary>
/// All linear algebra operations with Vec2 have to go through this wrapper.
/// We can work as if we have a standard coordinate system, instead of the flipped-y one, like in SDL.
/// </summary>
class Direction {
public:
	Direction(const Vec2& dir) : _dir(Vec2(dir.x, dir.y /* Negate y to adjust to the top-left origin and y increasing from top to bottom. */)) {}

	Vec2 getScreenSpace() const {
		return _dir;
	}

	Vec2 getWorldSpace() const {
		return Vec2(_dir.x, _dir.y);
	}

private:
	Vec2 _dir; // in screen space
};

#endif // !ENGINE_MATH_DIRECTION_H
