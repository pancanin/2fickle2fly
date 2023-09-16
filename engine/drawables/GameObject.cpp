#include "GameObject.h"

GameObject::GameObject(const Rect& r, float v, Vec2 d): rect(r), speed(v), dir(d)
{
}

GameObject::GameObject(const Rect& r) : GameObject(r, 0.0f, Vec2{})
{
}

Rect GameObject::getRect() const
{
	return rect;
}

void GameObject::moveAlong()
{
	Vec2 currentPos(rect._rect.x, rect._rect.y);
	Vec2 newPos = currentPos + (dir * speed);
	rect._rect.x = newPos.x;
	rect._rect.y = newPos.y;
}
