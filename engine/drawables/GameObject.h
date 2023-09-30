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

	/// <summary>
	/// Speed in pixels per frame.
	/// We might need something more real-world later on.
	/// </summary>
	void setSpeed(float);
	void steer(const Vec2& newDir);
//private:
	ID id;
	Rect rect;
	float speed; // pixels per second
	Direction direction;
};

struct GameObjectFactory {
	static GameObject createImmovableObject(const Vec2& pos, float w, float h, const Color& color) {
		return createObject(pos, w, h, color, 0.0f);
	}

	static GameObject createObject(const Vec2& pos, float w, float h, const Color& color, float speed) {
		return GameObject(Rect::Factory::createStandardRect(pos.x, pos.y, w, h, color), speed, Vec2());
	}

	// All segments of the underlying rectangle will have the same normal. This is useful for objects which have only one side facing the gameplay.
	static GameObject createSameNormalsObject(const Vec2& n, const Vec2& pos, float w, float h, const Color& color) {
		return GameObject(Rect::Factory::createCustomNormalsRect(n, n, n, n, pos.x, pos.y, w, h, color));
	}
};

#endif // !ENGINE_DRAWABLES_GAMEOBJECT_H
