#include "CollisionDetector.h"

void CollisionDetector::checkCollisions(std::vector<GameObject>& objs, CollisionCallback cb) const
{
	for (size_t i = 0; i < objs.size(); ++i) {
		GameObject& o1 = objs[i];
		const BoundingBox& b1 = o1.getRect().toBoundingBox();
		
		for (size_t j = i + 1 /* don't cross check objects */; j < objs.size(); ++j) {
			GameObject& o2 = objs[j];
			const BoundingBox& b2 = o2.getRect().toBoundingBox();
			
			if (b1.intersects(b2)) {
				cb(o1, o2);
			}
		}
	}
}

bool CollisionDetector::checkCollisions(GameObject& o1, std::vector<GameObject>& objs) const
{
	bool hasCollidedWithO1 = false;

	checkCollisions(objs, [&hasCollidedWithO1, &o1](GameObject& ob1, GameObject& ob2) {
		if (ob1.getId() == o1.getId() || ob2.getId() == o1.getId()) {
			hasCollidedWithO1 = true;
		}
	});

	return hasCollidedWithO1;
}
