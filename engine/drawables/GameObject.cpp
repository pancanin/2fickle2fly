#include "GameObject.h"

#include "engine/physics/collisions/CollisionData.h"

GameObject::GameObject(const Rect& r, float v, Vec2 d): rect(r), speed(v), direction(d) {}

GameObject::GameObject(const Rect& r) : GameObject(r, 0.0f, Vec2{})
{
}

const Rect& GameObject::getRect() const
{
	return rect;
}

void GameObject::updatePosition()
{
	Vec2 currentPos(rect.getX(), rect.getY());
	Vec2 newPos = currentPos + (direction.getScreenSpace() * speed);
 	this->rect.updatePosition(newPos);
}

void GameObject::setPosition(const Vec2& p)
{
	this->rect.updatePosition(p);
}

void GameObject::bounceOff(const CollisionData& c)
{
	this->setDirection(this->direction.getWorldSpace().reflect(c.o2N));
}

void GameObject::setSpeed(float v)
{
	this->speed = v;
}

void GameObject::setDirection(const Vec2& newDir)
{
	// The code below is for smoother movement. It is still not great because it does not take into account the current speed.
	// this->direction = this->direction + newDir;
	this->direction = Direction(newDir);
}

float GameObject::getSpeed() const
{
	return speed;
}

Direction GameObject::getDirection() const
{
	return direction;
}
