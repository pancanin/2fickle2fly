#ifndef ENGINE_DRAWABLES_GAMEOBJECT_H
#define ENGINE_DRAWABLES_GAMEOBJECT_H

#include "engine/drawables/Rect.h"
#include "engine/math/Vec2.h"
#include "engine/math/Direction.h"
#include "engine/misc/ID.h"

struct CollisionData;

struct GameObject {
	GameObject(const Rect&, float speed, Vec2 direction);
	GameObject(const Rect&);

	ID getId() const;
	void setId(ID id);

	const Rect& getRect() const;

	void updatePosition();
	void bounceOff(const CollisionData&);

	/// <summary>
	/// Speed in pixels per frame.
	/// We might need something more real-world later on.
	/// </summary>
	void setSpeed(float);
	void steer(const Vec2& newDir);
//private:
	ID id;
	Rect rect;
	float speed; // current speed pixels per second
	Direction direction;
};

struct GameObjectFactory {
	static GameObject createImmovableObject(const Vec2& pos, float w, float h, const Color& color) {
		return createObject(pos, w, h, color, 0.0f);
	}

	static GameObject createImmovableObject(const Vec2& pos, float w, float h) {
		return createObject(pos, w, h, Color{}, 0.0f);
	}

	static GameObject createObject(const Vec2& pos, float w, float h, const Color& color, float speed) {
		return GameObject(Rect::Factory::createRect(pos.x, pos.y, w, h, color), speed, Vec2());
	}

	static GameObject createObject(const Vec2& pos, float w, float h, const Color& color, float speed, const Vec2& dir) {
		return GameObject(Rect::Factory::createRect(pos.x, pos.y, w, h, color), speed, dir);
	}
};

#endif // !ENGINE_DRAWABLES_GAMEOBJECT_H
