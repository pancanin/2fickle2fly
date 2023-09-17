#ifndef PLATFORM_IDS_FORWARDIDGENERATOR_H_
#define PLATFORM_IDS_FORWARDIDGENERATOR_H_

#include <cstdint>

#include "engine/misc/ID.h"

class ForwardIdGenerator {
public:
	ForwardIdGenerator() : id(0) {}

	ID next() {
		return id++;
	}
private:
	ID id;
};

#endif /* PLATFORM_IDS_FORWARDIDGENERATOR_H_ */
