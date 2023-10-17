#include "CollisionDetector.h"

void CollisionDetector::checkCollisions(const std::vector<GameObject>& objs, CollisionCallback cb) const
{
	for (size_t i = 0; i < objs.size(); ++i) {
		const GameObject& o1 = objs[i];
		// TODO: I think the problem is here: we are returning a copy and after each checkCollision there are changes with the objects.
		// Also, there are objects that are used controlled which should not be 'separated'.
		// All objects that bounce off stuff should be separated
		const BoundingBox& b1 = o1.getRect().toBoundingBox();
		
		for (size_t j = i + 1 /* don't cross check objects */; j < objs.size(); ++j) {
			const GameObject& o2 = objs[j];
			const BoundingBox& b2 = o2.getRect().toBoundingBox();
			
			if (b1.intersects(b2)) {
				cb(o1, o2);
			}
		}
	}
}

bool CollisionDetector::checkCollisions(const GameObject& o1, const std::vector<GameObject>& objs) const
{
	bool hasCollidedWithO1 = false;

	checkCollisions(objs, [&hasCollidedWithO1, &o1](const GameObject& ob1, const GameObject& ob2) {
		if (ob1.getId() == o1.getId() || ob2.getId() == o1.getId()) {
			hasCollidedWithO1 = true;
		}
	});

	return hasCollidedWithO1;
}

bool CollisionDetector::checkCollisions(const GameObject& o1, const GameObject& o2) const
{
	return checkCollisions(o1, { o2 });
}
