#ifndef GAMES_BREAKOUT
#define GAMES_BREAKOUT

#include "engine/GameEngine.h"

class EventEmitter;
struct GameObject;

class Breakout : public GameEngine {
private:
	void onStart() override;
	void setKeyBindings(EventEmitter&) override;
	void onUpdate() override;
	void handleCollision(const CollisionData&) override;

	void buildSideWalls();

	GameObject* paddle = nullptr;
	GameObject* obstacle = nullptr;
	float padding = 2.0f;
	float brickWidth = 32.0f;
	float brickHeight = 16.0f;
};

#endif // !GAMES_BREAKOUT
