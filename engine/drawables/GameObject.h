#ifndef ENGINE_DRAWABLES_GAMEOBJECT_H
#define ENGINE_DRAWABLES_GAMEOBJECT_H

#include "engine/drawables/Rect.h"
#include "engine/math/Vec2.h"

struct GameObject {
	GameObject(const Rect&, float speed, Vec2 dir);
	GameObject(const Rect&);

	Rect getRect() const;

	void moveAlong();
private:
	Rect rect;
	float speed; // pixels per second
	Vec2 dir;
};

#endif // !ENGINE_DRAWABLES_GAMEOBJECT_H
