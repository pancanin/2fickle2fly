#include "Breakout.h"

#include <iostream>
#include <math.h>

#include "engine/math/Vec2.h"
#include "engine/drawables/GameObject.h"
#include "engine/input/EventEmitter.h"
#include "engine/physics/collisions/CollisionData.h"
#include "engine/physics/collisions/CollisionResolver.h"
#include "engine/physics/collisions/CollisionDetector.h"
#include "ui/ProgressBar.h"

uint32_t padding = 2;
uint32_t brickWidth = 32;
uint32_t brickHeight = 16;
float ballSpeed = 13.0f;
float paddleSpeed = 8.0f;
uint32_t paddleWidth = 128;
uint32_t paddleHeight = 32;

void Breakout::onStart()
{
  showGameScreen();
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
      ball.setDirection(Vec2(-1.0f, -1.0f));
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
      ball.takeControl();
      ball.makeDirChangeable();
      ball.setDirection(Vec2(0.0f, 0.0f));
      ball.setPosition(initBallPos);
      GameObject& paddle = objects.get(paddleId);
      paddle.setPosition(initialPaddlePos);
      auto& livesBar = progressBars.get(livesBarId);
      livesBar.decrement();

      if (lives == 0) {
        state = GameState::GAME_OVER;
      }
      else {
        state = GameState::READY;
      }
    }
  }
}

static Vec2 getNormalAtHit(int x, int yd, int ballSize, GameObject& ball) {
  const bool isOnLeftSide = x <= 0 && yd >= 0;
  const bool isOnRightSide = x >= 128 && yd >= 0;

  if (isOnLeftSide) {
    ball.makeFreeFalling();
    return Vec2(-1, 0);
  }
  else if (isOnRightSide) {
    ball.makeFreeFalling();
    return Vec2(1, 0);
  }
  if (x < 32) {
    return Vec2(-std::cos(M_PI / 2.2f), -std::sin(M_PI / 2.2f));
  }
  else if (x >= 32 && x < 96) {
    return Vec2(0, -1);
  }
  else if (x >= 96 && x < 128) {
    return Vec2(std::cos(M_PI / 2.2f), -std::sin(M_PI / 2.2f));
  }
  else if (x >= 128) {
    return Vec2(1, 0);
  }
}

void Breakout::handleCollision(const CollisionData& collision)
{
  // Handle ball collision
  CollisionData c = collision.query(ballId);
  if (c.hasCollision) {
    GameObject& ball = objects.get(c.o1Id);
    
    

    if (bricks.find(c.o2Id) != bricks.end()) {
      // We hit a brick, destroy it.
      bricks.erase(c.o2Id);
      objects.remove(c.o2Id);
    }
    else if (collision.query(paddleId).hasCollision) {
      auto& paddle = objects.get(c.o2Id);
      float d = ball.getRect().getX() - paddle.getRect().getX();
      float yd = ball.getRect().getX() + ball.getRect().getHeight() - paddle.getRect().getX();
      Vec2 normal = getNormalAtHit(d, yd, ball.getRect().getWidth(), ball);
      c.o2N = normal;
    }

    ball.bounceOff(c);
  }

  // Handle paddle collisions
  c = collision.query(paddleId);
  if (c.hasCollision) {
    auto& paddle = objects.get(c.o1Id);

    if (ballId != c.o2Id) { // It is not a collision with the ball
      hasPaddleCollided = true;
      paddle.setSpeed(0.0);
    }

    paddleObstacleN = c.o2N;
  }

  
}

void Breakout::buildSideWalls()
{
  Color sidewallColor{ 128, 128, 128, 255 };

  // Upper wall
  objects.add(GameObjectFactory::createImmovableObject(Vec2(0, 0), getWindowWidth(), brickHeight, sidewallColor));

  // Left wall
  objects.add(GameObjectFactory::createImmovableObject(Vec2(0, brickHeight + padding), brickHeight, getWindowHeight(), sidewallColor));

  // Right wall
  objects.add(GameObjectFactory::createImmovableObject(Vec2(getWindowWidth() - brickHeight - padding, brickHeight + padding), brickHeight, getWindowHeight(), sidewallColor));
}

void Breakout::clearScreen()
{
}

void Breakout::showGameScreen()
{
  objects.init(30);

  uint32_t ballDim = 16;
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
  ID bbluebrick = addTexture("../games/breakout/resources/bblue.png");
  Texture& btex = textures.get(bbluebrick);
  for (auto& o : objs) {
    ID brickId = add(o);
    bricks.insert(brickId);
    auto& brick = objects.get(brickId);
    brick.setTexture(btex);
  }

  ID pikaId = addTexture("../games/breakout/resources/paddle.png");
  Texture& tex = textures.get(pikaId);
  auto& paddle = objects.get(paddleId);
  paddle.setTexture(tex);

  ID ballTexId = addTexture("../games/breakout/resources/ball.png");
  Texture& texball = textures.get(ballTexId);
  auto& ball = objects.get(ballId);
  ball.setTexture(texball);

  ID heartTexId = addTexture("../games/breakout/resources/heart.png");
  Texture heartTex = textures.get(heartTexId);
  UITex heartuiTex(heartTex, Rect::Factory::createRect(0, 0, 32, 32, Color{}));
  ProgressBar liveBar(heartuiTex, lives);
  livesBarId = add(liveBar);
}
