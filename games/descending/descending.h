#ifndef DESCENDING_GAME
#define DESCENDING_GAME

#include <memory>

#include "engine/GameEngine.h"

class Descending : public GameEngine {
public:
	Descending() : GameEngine(820, 640, 30) {}
private:
	ID heroId;

	void onStart() override;
	void setKeyBindings(EventEmitter&) override;
	void onUpdate() override;
	void handleCollision(const CollisionData&) override;
};

#endif // !DESCENDING_GAME
