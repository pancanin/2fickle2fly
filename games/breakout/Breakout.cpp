#include "Breakout.h"

#include "engine/drawables/GameObject.h"
#include "engine/input/EventEmitter.h"

void Breakout::onStart()
{
  buildSideWalls(); // if this is called after the below lines, the pointers are no longer valid due to resizing.
  // Check why does the vector resize, even after reserving capacity.
	paddle = add(GameObjectFactory::create(Vec2(100, 100), 100, 100, Color{ 255, 0, 0, 255 }));
  paddle->setSpeed(1.0f);

  obstacle = add(GameObjectFactory::create(Vec2(150, 150), 100, 100, Color{ 255, 0, 0, 255 }));
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
  if (collision.hasCollision) {
    obstacle->rect.color.g = 255;
  }
  else {
    obstacle->rect.color.g = 0;
  }
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
    add(GameObjectFactory::create(Vec2(i, 0), brickWidth, brickHeight, sidewallColor));
  }
}
