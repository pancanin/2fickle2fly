#ifndef TETRIS_H
#define TETRIS_H

#include "engine/GameEngine.h"

class Tetris : public GameEngine {
public:
	Tetris() : GameEngine(640, 480, 30) {}
private:
	void onStart() override;
	void setKeyBindings(EventEmitter&) override;
	void onUpdate() override;
	void handleCollision(const CollisionData&) override;
};

#endif // !TETRIS_H
