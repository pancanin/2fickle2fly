#ifndef GAMES_BREAKOUT
#define GAMES_BREAKOUT

#include "engine/GameEngine.h"

#include "engine/misc/ID.h"
#include "games/breakout/levels/LevelBuilder.h"

class EventEmitter;
struct GameObject;

class Breakout : public GameEngine {
public:
	Breakout() : GameEngine(640, 480, 30) {}
private:
	void onStart() override;
	void setKeyBindings(EventEmitter&) override;
	void onUpdate() override;
	void handleCollision(CollisionResolver&, CollisionDetector& d, const CollisionData&) override;

	/// <summary>
	/// Might be not needed in the future if we have a flag on which objects we need to unstuck.
	/// Generally objects that are not under user control and have > 0 speed need to get unstuck.
	/// This method allows the client to decide which objects needs unstucking.
	/// </summary>
	void resolveCollision(CollisionResolver&, const CollisionData&) override;

	void buildSideWalls();

private:
	LevelBuilder levelBuilder;
	ID paddleId = -1;
	ID ballId = -1;
	uint32_t padding = 2;
	uint32_t brickWidth = 32;
	uint32_t brickHeight = 16;
	float paddleSpeed = 5.0f;

	bool hasPaddleCollided = false; // used for disabling user-initiated movement of the paddle while collided with a non-ball.
	Vec2 paddleObstacleN; // The normal of the object which collided with the paddle. Need this to decide whether to move in a direction. Cleared in onUpdate.

	inline bool canMoveInDir(const Vec2& dir) const {
		Vec2 collideF = dir + paddleObstacleN;
		bool areNegated = collideF.x == 0.0f && collideF.y == 0.0f;
		return !(hasPaddleCollided && areNegated);
	}
};

#endif // !GAMES_BREAKOUT
