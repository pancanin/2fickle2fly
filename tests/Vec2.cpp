#include "engine/math/Vec2.h"

int main() {
	Vec2 a{ 1, 1 };
	Vec2 b{ 2, 4 };
	Vec2 c = a + b;

	if (c.x == 3 && c.y == 5) {
		return 0;
	}
	return 1;
}