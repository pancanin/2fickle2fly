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
	Vec2 newIterPos = direction.getScreenSpace();
	if (!newIterPos.isZero()) {
		while (newIterPos.length() < speed) {
			newIterPos = newIterPos + direction.getScreenSpace();
		}
	}
	Vec2 newPos = currentPos + newIterPos;
 	this->rect.updatePosition(newPos);
}

void GameObject::setPosition(const Vec2& p)
{
	this->rect.updatePosition(p);
}

void GameObject::bounceOff(const CollisionData& c)
{
	//if (unchangeableDir) return;
	this->prevDir = (this->prevDir.getWorldSpace().reflect(c.o2N).normalized());

	/*if (isFreeFalling) {
		unchangeableDir = true;
	}*/
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

void GameObject::setTexture(const Texture& texture)
{
	this->texture = texture;
	this->hasTexture = true;
}

const Texture& GameObject::getTexture() const
{
	return texture;
}

void GameObject::makeFreeFalling()
{
	this->isFreeFalling = true;
}

void GameObject::makeDirChangeable()
{
	unchangeableDir = false;
}

void GameObject::takeControl()
{
	this->isFreeFalling = false;
}

void GameObject::stop()
{
	prevDir = direction;
	prevSpeed = speed;
	direction = Vec2();
	speed = 0.0f;
}

void GameObject::start()
{
 	direction = prevDir;
	speed = prevSpeed;
}
