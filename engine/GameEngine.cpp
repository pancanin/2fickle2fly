#include "GameEngine.h"

#include "osplatform/Time.h"

void GameEngine::start() {
  onStart();
	//Time stopwatch;

	while (!stop) {
		//stopwatch.getElapsed();
		/*bool hasEvents = inputComponent.poll();

		if (inputComponent.hasExitEvent()) {
			break;
		}*/

		handleEvent();

		onUpdate();

		// Frame rate control
		/*Time& clockedTime = stopwatch.getElapsed();
		float timeLeftInFrame = 16 - clockedTime.toMilliseconds();
		ThreadUtils::sleepFor(timeLeftInFrame);*/
	}
}

void GameEngine::setTargetFrameRate(float frameRate)
{
	this->frameRate = frameRate;
}
