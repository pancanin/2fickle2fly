#include "GameObject.h"

#include "engine/physics/collisions/CollisionData.h"

GameObject::GameObject(const Rect& r, float v, Vec2 d): id(0), rect(r), speed(v), direction(d) {}

GameObject::GameObject(const Rect& r) : GameObject(r, 0.0f, Vec2{})
{
}

ID GameObject::getId() const
{
	return id;
}

void GameObject::setId(ID id)
{
	this->id = id;
}

Rect GameObject::getRect() const
{
	return rect;
}

void GameObject::updatePosition()
{
	Vec2 currentPos(rect.getX(), rect.getY());
	Vec2 newPos = currentPos + (direction.getScreenSpace() * speed);
	this->rect.updatePosition(newPos);
}

void GameObject::bounceOff(const CollisionData& c)
{
	this->steer(this->direction.getWorldSpace().reflect(c.o2N));
}

void GameObject::setSpeed(float v)
{
	this->speed = v;
}

void GameObject::steer(const Vec2& newDir)
{
	// The code below is for smoother movement. It is still not great because it does not take into account the current speed.
	// this->direction = this->direction + newDir;
	this->direction = Direction(newDir);
}
