#ifndef GAMES_BREAKOUT_LEVEL_BUILDER
#define GAMES_BREAKOUT_LEVEL_BUILDER

#include <cstdint>
#include <vector>

#include "engine/drawables/GameObject.h"

#define MAX_LEVELS 5
#define BRICKS_FIELD_WIDTH 10
#define BRICKS_FIELD_HEIGHT 6
#define BRICK_WIDTH 32
#define BRICK_HEIGHT 16 // These all properties should be in a config file probably. But as the levels are not dynamic I leave them here.
#define FIELD_OFFSET_X 50
#define FIELD_OFFSET_Y 80
#define PADDING 2

/// <summary>
/// A level, in the context of Breakout game, is a rectangular grid with cells and each cell may or may not have a brick in it.
/// For now, the level dimensions are not dynamic.
/// This class is *very* concrete and its purpose is to build Breakout levels.
/// </summary>
class LevelBuilder {
public:
	void addLevel(char level[BRICKS_FIELD_HEIGHT][BRICKS_FIELD_WIDTH]);
	std::vector<GameObject> build(uint32_t lvlIdx) const;
private:
	char levels[MAX_LEVELS][BRICKS_FIELD_HEIGHT][BRICKS_FIELD_WIDTH];
	uint32_t counter = 0;
};

#endif // !GAMES_BREAKOUT_LEVEL_BUILDER
