#ifndef ENGINE_DRAWABLES_GAMEOBJECT_H
#define ENGINE_DRAWABLES_GAMEOBJECT_H

#include "engine/drawables/Rect.h"
#include "engine/math/Vec2.h"
#include "engine/math/Direction.h"
#include "engine/misc/Identifiable.h"
#include "api/sdl/texture/Texture.h"

struct CollisionData;

struct GameObject : public Identifiable {
	GameObject(const Rect&, float speed, Vec2 direction);
	GameObject(const Rect&);

	const Rect& getRect() const;

	void updatePosition();
	void setPosition(const Vec2&);
	void bounceOff(const CollisionData&);

	/// <summary>
	/// Speed in pixels per frame.
	/// We might need something more real-world later on.
	/// </summary>
	void setSpeed(float);
	void setDirection(const Vec2& newDir);
	float getSpeed() const;
	Direction getDirection() const;
	void setTexture(const Texture&);
	const Texture& getTexture() const;
	inline bool isWithTexture() const {
		return hasTexture;
	}
private:
	Rect rect;
	float speed; // current speed pixels per second
	Direction direction;
	bool hasTexture = false;
	Texture texture;
};

struct GameObjectFactory {
	static GameObject createImmovableObject(const Vec2& pos, float w, float h, const Color& color) {
		return createObject(pos, w, h, color, 0.0f);
	}

	static GameObject createImmovableObject(const Vec2& pos, float w, float h) {
		return createObject(pos, w, h, Color{}, 0.0f);
	}

	static GameObject createObject(const Vec2& pos, float w, float h, const Color& color, float speed) {
		return createObject(pos, w, h, color, speed, Vec2());
	}

	// This method generates an ID for the object. Make sure to call this method from within other factory methods.
	static GameObject createObject(const Vec2& pos, float w, float h, const Color& color, float speed, const Vec2& dir) {
		return GameObject(Rect::Factory::createRect(pos.x, pos.y, w, h, color), speed, dir);
	}
};

#endif // !ENGINE_DRAWABLES_GAMEOBJECT_H
