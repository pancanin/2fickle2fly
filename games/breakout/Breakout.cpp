#include "Breakout.h"

#include "engine/drawables/GameObject.h"
#include "engine/input/EventEmitter.h"

void Breakout::onStart()
{
	paddle = add(GameObjectFactory::create(Vec2(100, 100), 100, 100, Color{ 255, 0, 0, 255 }));
  paddle->setSpeed(1.0f);
}

void Breakout::setKeyBindings(EventEmitter& ee)
{
  ee.listen(Key::UP, [this](Event e) { paddle->steer(Vec2(0.0f, 1.0f)); });
  ee.listen(Key::DOWN, [this](Event e) { paddle->steer(Vec2(0.0f, -1.0f)); });
  ee.listen(Key::LEFT, [this](Event e) { paddle->steer(Vec2(-1.0f, 0.0f)); });
  ee.listen(Key::RIGHT, [this](Event e) { paddle->steer(Vec2(1.0f, 0.0f)); });
}

void Breakout::onUpdate()
{
}

void Breakout::handleCollision(const CollisionData& collision)
{
}
