#include "GameEngine.h"

#include <iostream>

#include "osplatform/Time.h"
#include "osplatform/ThreadUtils.h"

#define MILLIS_IN_SECOND 1000

GameEngine::GameEngine(uint32_t w, uint32_t h, uint32_t frameRate):
	stop(false), width(w), height(h), frameDurationMs(MILLIS_IN_SECOND / frameRate)
{
}

int32_t GameEngine::init(const std::string& windowLabel)
{
	if (sdlInit.requireVideo().init() != 0 || window.init(windowLabel, width, height) != 0 ||
			rend.init(window, Color{}) != 0) {
		return -1;
	}

	// Setup some common key-bindings for every game.
	ee.listen(Key::ESC, ActionType::KEYDOWN, [this](Event e) { stop = true; });

	return 0;
}

void GameEngine::start() {
  onStart();
	setKeyBindings(ee);
	Time stopwatch;

	while (!stop) {
		stopwatch.getElapsed();
		
		rend.clear();
		ee.poll();
		
		for (auto& o : objects.elements()) {
			o.updatePosition();
		}
		onUpdate();

		// Collisions
		detector.checkCollisions(objects.elements(), [this](const GameObject& o1, const GameObject& o2) {
			if ((collisionResolver.shouldSeparate(o1.getId()) && collisionResolver.shouldSeparate(o2.getId()))) {
				collisionResolver.separateObjects(const_cast<GameObject&>(o2), objects.elements());
			}
			else {
				collisionResolver.separateObjects(const_cast<GameObject&>(o1), objects.elements());
				collisionResolver.separateObjects(const_cast<GameObject&>(o2), objects.elements());
			}
			Vec2 o1N = aggre.calculateHitNormal(o1, o2);
			Vec2 o2N = aggre.calculateHitNormal(o2, o1);
			CollisionData c(o1.getId(), o2.getId(), o1N, o2N);
			handleCollision(c);
		});

		for (auto& o : objects.elements()) {
			if (rend.render(o) != 0) {
				std::cout << error.getError();
			}
		}

		rend.update();

		// Frame rate control
		Time& clockedTime = stopwatch.getElapsed();
		int64_t timeLeftInFrame = frameDurationMs - clockedTime.toMilliseconds();
#if !NDEBUG
		// If we are debugging, the time left would be negative, because we paused on breakpoints for too long.
		// Set some constant sleep time for these cases.
#define SLEEP_TIME_IN_DEBUG 100
		if (timeLeftInFrame < 0) {
			timeLeftInFrame = SLEEP_TIME_IN_DEBUG;
		}
#undef SLEEP_TIME_IN_DEBUG
#endif
		ThreadUtils::sleepFor(timeLeftInFrame);
	}
}

ID GameEngine::add(const GameObject& obj)
{
	GameObject temp = obj;
	temp.setId(idGen.next());
	objects.add(temp);
	return temp.getId();
}

uint32_t GameEngine::getWindowWidth() const
{
	return width;
}

uint32_t GameEngine::getWindowHeight() const
{
	return height;
}
