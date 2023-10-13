#include "CollisionDetector.h"

void CollisionDetector::checkCollisions(const std::vector<GameObject>& objs, CollisionCallback cb) const
{
	for (size_t i = 0; i < objs.size(); ++i) {
		const GameObject& o1 = objs[i];
		const BoundingBox b1 = o1.getRect().toBoundingBox();
		
		for (size_t j = i + 1 /* don't cross check objects */; j < objs.size(); ++j) {
			const GameObject& o2 = objs[j];
			const BoundingBox b2 = o2.getRect().toBoundingBox();
			
			if (b1.intersects(b2)) {
				cb(o1, o2);
			}
		}
	}
}


