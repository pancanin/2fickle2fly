#include "GameEngine.h"

#include <iostream>

#include "osplatform/Time.h"
#include "osplatform/ThreadUtils.h"
#include "engine/physics/collisions/CollisionDetector.h"
#include "engine/physics/collisions/CollisionAggregator.h"
#include "engine/physics/collisions/Segmenter.h"

GameEngine::GameEngine(): stop(false), frameDurationMs(1000 / 30), width(0), height(0)
{
}

int32_t GameEngine::init(uint32_t w, uint32_t h)
{
	if (sdlInit.requireVideo().init() != 0) {
		return -1;
	}
	if (window.init("Test", w, h) != 0) { // TODO: These should be parameters
		return -1;
	}
	if (rend.init(window, Color{}) != 0) {
		return -1;
	}

	this->width = w;
	this->height = h;

	// This has to be done based on the game...So the game should call such allocations.
	objects.init(30);

	ee.listen(Key::ESC, [this](Event e) { stop = true; });

	return 0;
}

void GameEngine::start() {
  onStart();
	setKeyBindings(ee);
	Time stopwatch;
	Segmenter seg(5);
	CollisionDetector detector(seg);
	CollisionAggregator aggre;

	while (!stop) {
		stopwatch.getElapsed();
		
		rend.clear();
		ee.poll();
		
		for (auto& o : objects.elements()) {
			o.updatePosition();
		}
		onUpdate();

		CollisionData collision = aggre.aggregateCollisions(detector.checkCollisions(objects.elements()));
		handleCollision(collision);

		for (auto& o : objects.elements()) {
			if (rend.render(o) != 0) {
				std::cout << error.getError();
			}
		}

		rend.update();

		// Frame rate control
		Time& clockedTime = stopwatch.getElapsed();
		int64_t timeLeftInFrame = frameDurationMs - clockedTime.toMilliseconds();
		ThreadUtils::sleepFor(timeLeftInFrame);
	}
}

GameObject* GameEngine::add(const GameObject& obj)
{
	GameObject temp = obj;
	temp.setId(idGen.next());
	return &objects.add(obj);
}

uint32_t GameEngine::getWindowWidth() const
{
	return width;
}

uint32_t GameEngine::getWindowHeight() const
{
	return height;
}

void GameEngine::setTargetFrameRate(uint32_t frameRate)
{
	this->frameDurationMs = 1000 / frameRate;
}
