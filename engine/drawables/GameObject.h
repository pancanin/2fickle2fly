#ifndef ENGINE_DRAWABLES_GAMEOBJECT_H
#define ENGINE_DRAWABLES_GAMEOBJECT_H

#include "engine/drawables/Rect.h"
#include "engine/math/Vec2.h"
#include "engine/math/Direction.h"

struct GameObject {
	GameObject(const Rect&, float speed, Vec2 direction);
	GameObject(const Rect&);

	Rect getRect() const;

	void updatePosition();
	void setSpeed(float);
	void steer(const Vec2& newDir);
private:
	Rect rect;
	float speed; // pixels per second
	Direction direction;
};

#endif // !ENGINE_DRAWABLES_GAMEOBJECT_H
