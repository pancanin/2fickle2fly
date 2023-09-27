#include "Breakout.h"

#include "engine/math/Vec2.h"
#include "engine/drawables/GameObject.h"
#include "engine/input/EventEmitter.h"

void Breakout::onStart()
{
  objects.init(30);

  uint32_t paddleWidth = 128;
  uint32_t paddleHeight = 32;
  Vec2 initialPaddlePos = Vec2(getWindowWidth() / 2, getWindowHeight() - paddleHeight);

	paddleId = add(GameObjectFactory::createObject(initialPaddlePos, paddleWidth, paddleHeight, Color{ 255, 0, 0, 255 }, 4.0f));

  auto ballDim = 16;
  auto initBallPos = Vec2(getWindowWidth() / 2, getWindowHeight() / 2);
	ballId = add(GameObjectFactory::createObject(initBallPos, ballDim, ballDim, Color{ 20, 130, 40, 255 }, 5.0f));

  buildSideWalls();
}

void Breakout::setKeyBindings(EventEmitter& ee)
{
  // Hmmm, don' we have to get the paddle in the lambda itself?
  GameObject& paddle = objects.get(paddleId);
  ee.listen(Key::LEFT, [&paddle](Event e) { paddle.steer(Vec2(-1.0f, 0.0f)); });
  ee.listen(Key::RIGHT, [&paddle](Event e) { paddle.steer(Vec2(1.0f, 0.0f)); });

  GameObject& ball = objects.get(ballId);
  ee.listen(Key::SPACE, [&ball](Event e) { ball.steer(Vec2(0.0f, 1.0f)); });
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
