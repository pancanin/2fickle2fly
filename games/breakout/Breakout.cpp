#include "Breakout.h"

#include <iostream>

#include "engine/math/Vec2.h"
#include "engine/drawables/GameObject.h"
#include "engine/input/EventEmitter.h"
#include "engine/physics/collisions/CollisionData.h"
#include "engine/physics/collisions/CollisionResolver.h"
#include "engine/physics/collisions/CollisionDetector.h"

void Breakout::onStart()
{
  objects.init(30);

  uint32_t ballDim = 10;
  initialPaddlePos = Vec2(getWindowWidth() / 2, getWindowHeight() - paddleHeight);
  initBallPos = Vec2(initialPaddlePos.x, initialPaddlePos.y - ballDim);
	ballId = add(GameObjectFactory::createObject(initBallPos, ballDim, ballDim, Color{ 20, 130, 40, 255 }, ballSpeed));
  collisionResolver.addObjectForSeparation(ballId);

  paddleId = add(GameObjectFactory::createObject(initialPaddlePos, paddleWidth, paddleHeight, Color{ 255, 0, 0, 255 }, paddleSpeed));
  collisionResolver.addObjectForSeparation(paddleId);

  buildSideWalls();

  char level1[BRICKS_FIELD_HEIGHT][BRICKS_FIELD_WIDTH] = {
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    {' ','1','1','1','1','1','1','1','1',' '},
    {' ','1','1','1','1','1','1','1','1',' '},
    {' ','1','1','1','1','1','1','1','1',' '},
    {' ','1','1','1','1','1','1','1','1',' '},
    {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
  };
  levelBuilder.addLevel(level1);
  auto objs = levelBuilder.build(0);
  for (auto& o : objs) {
    ID oId = add(o);
    bricks.insert(oId);
  }

  addTexture("../games/breakout/resources/pika.png");
}

void Breakout::setKeyBindings(EventEmitter& ee)
{
  GameObject& paddle = objects.get(paddleId);
  ee.listen(Key::LEFT, ActionType::KEYDOWN, [&paddle, this](Event e) {
    Vec2 actionDir = Vec2(-1.0f, 0.0f);
    if (!canMoveInDir(actionDir)) { return; }
    paddle.setDirection(Vec2(-1.0f, 0.0f));
    paddle.setSpeed(paddleSpeed);
  });
  ee.listen(Key::RIGHT, ActionType::KEYDOWN, [&paddle, this](Event e) {
    Vec2 actionDir = Vec2(1.0f, 0.0f);
    if (!canMoveInDir(actionDir)) { return; }
    paddle.setDirection(Vec2(1.0f, 0.0f));
    paddle.setSpeed(paddleSpeed);
  });

  GameObject& ball = objects.get(ballId);
  ee.listen(Key::SPACE, ActionType::KEYDOWN, [&ball, this](Event e) {
    if (state == GameState::READY) {
      ball.setDirection(Vec2(1.0f, 1.0f));
      ball.setSpeed(ballSpeed);
      state = GameState::STARTED;
    }
  });

  auto movementKeysUpHandler = [&paddle, this](Event e) {
    paddle.setSpeed(0.0f);
    paddle.setDirection(Vec2(0.0f, 0.0f));
  };
  ee.listen(Key::LEFT, ActionType::KEYUP, movementKeysUpHandler);
  ee.listen(Key::RIGHT, ActionType::KEYUP, movementKeysUpHandler);
}

void Breakout::onUpdate()
{
  paddleObstacleN = Vec2();

  if (state == GameState::STARTED) {
    GameObject& ball = objects.get(ballId);

    // The ball flew off the bottom edge of the screen
    if (ball.getRect().getY() > getWindowHeight()) {
      lives--;
      std::cout << "You are left with " << lives << " lives\n";
      ball.setSpeed(0.0f);
      ball.setPosition(initBallPos);
      GameObject& paddle = objects.get(paddleId);
      paddle.setPosition(initialPaddlePos);

      if (lives == 0) {
        state = GameState::GAME_OVER;
      }
      else {
        state = GameState::READY;
      }
    }
  }
}

void Breakout::handleCollision(const CollisionData& collision)
{
  // Handle ball collision
  CollisionData c = collision.query(ballId);
  if (c.hasCollision) {
    GameObject& ball = objects.get(c.o1Id);
    
    ball.bounceOff(c);

    if (bricks.find(c.o2Id) != bricks.end()) {
      // We hit a brick, destroy it.
      bricks.erase(c.o2Id);
      objects.remove(c.o2Id);
    }
  }

  // Handle paddle collisions
  c = collision.query(paddleId);
  if (c.hasCollision) {
    auto& paddle = objects.get(c.o1Id);

    if (ballId != c.o2Id) { // It is not a collision with the ball
      hasPaddleCollided = true;
      paddle.setSpeed(0.0);
    }
    else {
      // Ball collision with paddle
      hasPaddleCollided = false;
      GameObject& ball = objects.get(c.o2Id);
      float d = ball.getRect().getX() - paddle.getRect().getX();

      if (ball.getRect().getY() + ball.getRect().getHeight() < paddle.getRect().getY()) {
        if (d < 32) {
          Vec2 rightN = Vec2(1.0f, 0.0f);
          Vec2 ballDir = ball.getDirection().getWorldSpace();
          float sameDir = rightN.dot(ballDir);
          if (sameDir >= 0.0f) {
            // The ball goes to the left, so bounce it back in the opposite direction.
            ball.setDirection(-ballDir);
          }
        }
        else if (d >= 96) {
          Vec2 leftN = Vec2(-1.0f, 0.0f);
          Vec2 ballDir = ball.getDirection().getWorldSpace();
          float sameDir = leftN.dot(ballDir);
          if (sameDir >= 0.0f) {
            // The ball goes to the left, so bounce it back in the opposite direction.
            ball.setDirection(-ballDir);
          }
        }
      }
    }
    paddleObstacleN = c.o2N;
  }
}

void Breakout::buildSideWalls()
{
  Color sidewallColor{ 128, 128, 128, 255 };

  // Upper wall
  add(GameObjectFactory::createImmovableObject(Vec2(0, 0), getWindowWidth(), brickHeight, sidewallColor));

  // Left wall
  add(GameObjectFactory::createImmovableObject(Vec2(0, brickHeight + padding), brickHeight, getWindowHeight(), sidewallColor));

  // Right wall
  add(GameObjectFactory::createImmovableObject(Vec2(getWindowWidth() - brickHeight - padding, brickHeight + padding), brickHeight, getWindowHeight(), sidewallColor));
}
