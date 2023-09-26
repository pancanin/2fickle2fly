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

	GameObject* paddle;
};

#endif // !GAMES_BREAKOUT
