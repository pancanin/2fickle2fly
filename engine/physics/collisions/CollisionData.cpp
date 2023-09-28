#include "CollisionData.h"

#include <utility>

CollisionData CollisionData::query(ID id) const
{
  if (this->o2Id == id) {
    CollisionData temp = *this;
    std::swap(temp.o1Id, temp.o2Id);
    std::swap(temp.o1N, temp.o2N);
    return temp;
  }
  else if (this->o1Id == id) {
    return *this;
  }
  else {
    return CollisionData();
  }
}
