#include "CollisionDetector.h"

CollisionDetector::CollisionDetector(const Segmenter& s): segmenter(s)
{
}

std::vector<CollisionData> CollisionDetector::checkCollisions(const std::vector<GameObject>& objs) const
{
	std::vector<CollisionData> collisions;

	for (size_t i = 0; i < objs.size(); ++i) {
		const GameObject& o1 = objs[i];

		for (size_t j = i + 1 /* don't cross check objects */; j < objs.size(); ++j) {
			const GameObject& o2 = objs[j];

			std::vector<Segment> o1Segments = segmenter.segment(o1.getRect().toWorldSpace());
			std::vector<Segment> o2Segments = segmenter.segment(o2.getRect().toWorldSpace());

			for (Segment& o1Seg : o1Segments) {
				for (Segment& o2Seg : o2Segments) {
					if (o1Seg.bb.intersects(o2Seg.bb)) {
						collisions.push_back(CollisionData(o1.getId(), o2.getId(), o1Seg.N, o2Seg.N));
					}
				}
			}
		}
	}

	return collisions;
}


