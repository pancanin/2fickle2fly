#include "Breakout.h"

#include <iostream>

#include "engine/math/Vec2.h"
#include "engine/drawables/GameObject.h"
#include "engine/input/EventEmitter.h"
#include "engine/physics/collisions/CollisionData.h"
#include "engine/physics/collisions/CollisionResolver.h"

void Breakout::onStart()
{
  objects.init(30);

  uint32_t paddleWidth = 128;
  uint32_t paddleHeight = 32;
  Vec2 initialPaddlePos = Vec2(getWindowWidth() / 2, getWindowHeight() - paddleHeight);

	paddleId = add(GameObjectFactory::createObject(initialPaddlePos, paddleWidth, paddleHeight, Color{ 255, 0, 0, 255 }, paddleSpeed));

  auto ballDim = 16;
  auto initBallPos = Vec2(getWindowWidth() / 2, getWindowHeight() / 2);
	ballId = add(GameObjectFactory::createObject(initBallPos, ballDim, ballDim, Color{ 20, 130, 40, 255 }, 4.0f));

  buildSideWalls();
}

void Breakout::setKeyBindings(EventEmitter& ee)
{
  // Hmmm, don' we have to get the paddle in the lambda itself?
  GameObject& paddle = objects.get(paddleId);
  ee.listen(Key::LEFT, ActionType::KEYDOWN, [&paddle, this](Event e) {
    paddle.steer(Vec2(-1.0f, 0.0f));
    paddle.setSpeed(paddleSpeed);
  });
  ee.listen(Key::RIGHT, ActionType::KEYDOWN, [&paddle, this](Event e) {
    paddle.steer(Vec2(1.0f, 0.0f));
    paddle.setSpeed(paddleSpeed);
  });

  GameObject& ball = objects.get(ballId);
  ee.listen(Key::SPACE, ActionType::KEYDOWN, [&ball](Event e) {
    ball.steer(Vec2(0.0f, 1.0f));
  });

  auto movementKeysUpHandler = [&paddle, this](Event e) {
    paddle.setSpeed(0.0f);
    paddle.steer(Vec2(0.0f, 0.0f));
  };
  ee.listen(Key::LEFT, ActionType::KEYUP, movementKeysUpHandler);
  ee.listen(Key::RIGHT, ActionType::KEYUP, movementKeysUpHandler);
}

void Breakout::onUpdate()
{
}

void Breakout::handleCollision(const CollisionData& collision)
{
  CollisionData c = collision.query(ballId);
  if (c.hasCollision) {
    GameObject& ball = objects.get(c.o1Id);
    ball.bounceOff(c);
  }
  c = collision.query(paddleId);
  if (c.hasCollision) {
    auto& paddle = objects.get(c.o1Id);
    paddle.setSpeed(0.0);
  }
}

void Breakout::resolveCollision(CollisionResolver& r, const CollisionData& c)
{
  CollisionData cQueried = c.query(ballId);
  if (cQueried.hasCollision) {
    GameObject& ball = objects.get(cQueried.o1Id);
    GameObject& other = objects.get(cQueried.o2Id);
    r.separateObjects(ball, other);
  }

  cQueried = c.query(paddleId);
  if (cQueried.hasCollision) {
    GameObject& paddle = objects.get(cQueried.o1Id);
    GameObject& other = objects.get(cQueried.o2Id);
    paddle.direction = Direction(-paddle.direction.getWorldSpace());
    r.separateObjects(paddle, other);
  }
}

void Breakout::buildSideWalls()
{
  Color sidewallColor{ 128, 128, 128, 255 };

  // Upper wall
  for (size_t i = padding; i < getWindowWidth(); i += padding + brickWidth) {
    add(GameObjectFactory::createEqualNormalsObject(Vec2(0, -1), Vec2(i, 0), brickWidth, brickHeight, sidewallColor));
  }

  // Left wall
  for (size_t i = brickHeight + padding; i < getWindowHeight(); i += padding + brickWidth) {
    add(GameObjectFactory::createEqualNormalsObject(Vec2(1, 0), Vec2(padding, i), brickHeight, brickWidth, sidewallColor));
  }

  // Right wall
  for (size_t i = brickHeight + padding; i < getWindowHeight(); i += padding + brickWidth) {
    add(GameObjectFactory::createEqualNormalsObject(Vec2(-1, 0), Vec2(getWindowWidth() - brickHeight - padding, i), brickHeight, brickWidth, sidewallColor));
  }
}
