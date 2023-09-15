#ifndef ENGINEV2_GAMEENGINE_H_
#define ENGINEV2_GAMEENGINE_H_

#include <string>
#include <cstdint>
#include <memory>

class GameEngine {
public:
  GameEngine() = default;
	virtual ~GameEngine() = default;
	void start();

	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void handleEvent() = 0;
	void setTargetFrameRate(float frameRate);
private:
	bool stop = false;
	uint32_t frameRate;
};

#endif /* ENGINEV2_GAMEENGINE_H_ */
