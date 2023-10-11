#include "LevelBuilder.h"

#include <assert.h>

void LevelBuilder::addLevel(char level[BRICKS_FIELD_HEIGHT][BRICKS_FIELD_WIDTH])
{
	assert(counter < MAX_LEVELS);
	
	for (size_t i = 0; i < BRICKS_FIELD_HEIGHT; i++) {
		for (size_t j = 0; j < BRICKS_FIELD_WIDTH; j++) {
			levels[counter][i][j] = level[i][j];
		}
	}
	counter++;
}

std::vector<GameObject> LevelBuilder::build(uint32_t lvlIdx) const
{
	assert(lvlIdx < MAX_LEVELS);

	std::vector<GameObject> objs;

	for (size_t i = 0; i < BRICKS_FIELD_HEIGHT; i++) {
		for (size_t j = 0; j < BRICKS_FIELD_WIDTH; j++) {
			char c = levels[lvlIdx][i][j];

			if (c != ' ') {
				Vec2 offpos(FIELD_OFFSET_X, FIELD_OFFSET_Y);
				Vec2 brickPosRel((j * BRICK_WIDTH) + PADDING, (i * BRICKS_FIELD_HEIGHT) + PADDING);
				objs.push_back(GameObjectFactory::createImmovableObject(offpos + brickPosRel, BRICK_WIDTH, BRICK_HEIGHT, Color{ 255, 0, 0, 255 }));
			}
		}
	}

	return objs;
}
