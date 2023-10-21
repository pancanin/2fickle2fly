#ifndef ENGINE_MISC_IDENTIFIABLE
#define ENGINE_MISC_IDENTIFIABLE

#include "engine/misc/ID.h"

class GameEngine;

class Identifiable {
public:
	friend class GameEngine;
	ID getId() const { return id; }
private:
	void setId(ID id) { this->id = id; }
	ID id;
};

#endif // !ENGINE_MISC_IDENTIFIABLE
