#ifndef GAMES_BREAKOUT
#define GAMES_BREAKOUT

#include <unordered_set>

#include "engine/GameEngine.h"

#include "engine/misc/ID.h"
#include "games/breakout/levels/LevelBuilder.h"

class EventEmitter;

enum class GameState {
	// Game screens before the actual game window
	NOT_STARTED,
	// Game window but the ball is not launched yet
	READY,
	// Game is on
	STARTED,
	// Lost all lives
	GAME_OVER
};

class Breakout : public GameEngine {
public:
	Breakout() : GameEngine(640, 480, 30) {}
private:
	void onStart() override;
	void setKeyBindings(EventEmitter&) override;
	void onUpdate() override;
	void handleCollision(const CollisionData&) override;
	void buildSideWalls();

	void clearScreen();
	void showGameScreen();
private:
	LevelBuilder levelBuilder;
	ID paddleId = -1;
	ID ballId = -1;
	Vec2 initialPaddlePos;
	Vec2 initBallPos;
	uint32_t padding = 2;
	uint32_t brickWidth = 32;
	uint32_t brickHeight = 16;
	float ballSpeed = 4.0f;
	float paddleSpeed = 5.0f;
	uint32_t paddleWidth = 128;
	uint32_t paddleHeight = 32;

	bool hasPaddleCollided = false; // used for disabling user-initiated movement of the paddle while collided with a non-ball.
	Vec2 paddleObstacleN; // The normal of the object which collided with the paddle. Need this to decide whether to move in a direction. Cleared in onUpdate.

	std::unordered_set<ID> bricks;

	GameState state = GameState::READY;
	uint32_t lives = 3;
	ID livesBarId;

	inline bool canMoveInDir(const Vec2& dir) const {
		Vec2 collideF = dir + paddleObstacleN;
		bool areNegated = collideF.x == 0.0f && collideF.y == 0.0f;
		return !(hasPaddleCollided && areNegated);
	}
};

#endif // !GAMES_BREAKOUT
