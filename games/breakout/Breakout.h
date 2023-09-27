#ifndef GAMES_BREAKOUT
#define GAMES_BREAKOUT

#include "engine/GameEngine.h"

#include "engine/misc/ID.h"

class EventEmitter;
struct GameObject;

class Breakout : public GameEngine {
public:
	Breakout() : GameEngine(640, 480, 30) {}
private:
	void onStart() override;
	void setKeyBindings(EventEmitter&) override;
	void onUpdate() override;
	void handleCollision(const CollisionData&) override;

	void buildSideWalls();

	ID paddleId = -1;
	uint32_t padding = 2;
	uint32_t brickWidth = 32;
	uint32_t brickHeight = 16;
};

#endif // !GAMES_BREAKOUT
