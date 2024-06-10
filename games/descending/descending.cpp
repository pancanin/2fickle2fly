#include "descending.h"

Vec2 heroPos(0, 0);

void Descending::onStart()
{
	ID heroTextureId = addTexture("../games/breakout/resources/ball.png");
	Texture& heroTexture = textures.get(heroTextureId);
	heroId = add(GameObjectFactory::createObject(heroPos, 64, 64, heroTexture, 5.0f));
}

void Descending::setKeyBindings(EventEmitter&)
{
}

void Descending::onUpdate()
{
}

void Descending::handleCollision(const CollisionData&)
{
}
