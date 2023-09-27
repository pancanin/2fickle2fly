#include "Breakout.h"

#include "engine/drawables/GameObject.h"
#include "engine/input/EventEmitter.h"

void Breakout::onStart()
{
  objects.init(30);
	paddleId = add(GameObjectFactory::createObject(Vec2(100, 100), 100, 100, Color{ 255, 0, 0, 255 }, 1.0f));

  buildSideWalls();
}

void Breakout::setKeyBindings(EventEmitter& ee)
{
  GameObject& paddle = objects.get(paddleId);
  ee.listen(Key::UP, [&paddle](Event e) { paddle.steer(Vec2(0.0f, 1.0f)); });
  ee.listen(Key::DOWN, [&paddle](Event e) { paddle.steer(Vec2(0.0f, -1.0f)); });
  ee.listen(Key::LEFT, [&paddle](Event e) { paddle.steer(Vec2(-1.0f, 0.0f)); });
  ee.listen(Key::RIGHT, [&paddle](Event e) { paddle.steer(Vec2(1.0f, 0.0f)); });
}

void Breakout::onUpdate()
{
}

void Breakout::handleCollision(const CollisionData& collision)
{
  
}

void Breakout::buildSideWalls()
{
  // have a variable that will be equal to the initial padding
  // start a loop with the variable to the max width of the screen
  // build a game object and add it to objects
  // increment the variable with padding + size of brick

  Color sidewallColor{ 128, 128, 128, 255 };

  // Upper wall
  for (size_t i = padding; i < getWindowWidth(); i += padding + brickWidth) {
    add(GameObjectFactory::createImmovableObject(Vec2(i, 0), brickWidth, brickHeight, sidewallColor));
  }
}
