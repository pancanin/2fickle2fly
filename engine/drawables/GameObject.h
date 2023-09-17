#ifndef ENGINE_DRAWABLES_GAMEOBJECT_H
#define ENGINE_DRAWABLES_GAMEOBJECT_H

#include "engine/drawables/Rect.h"
#include "engine/math/Vec2.h"
#include "engine/math/Direction.h"
#include "engine/misc/ID.h"

struct GameObject {
	GameObject(const Rect&, float speed, Vec2 direction);
	GameObject(const Rect&);

	ID getId() const;
	void setId(ID id);

	Rect getRect() const;

	void updatePosition();
	void setSpeed(float);
	void steer(const Vec2& newDir);
private:
	ID id;
	Rect rect;
	float speed; // pixels per second
	Direction direction;
};

struct GameObjectFactory {
	static GameObject create(const Vec2& pos, float w, float h, const Color& color) {
		return GameObject(Rect(pos.x, pos.y, w, h, color), 0.0f, Vec2());
	}
};

#endif // !ENGINE_DRAWABLES_GAMEOBJECT_H
