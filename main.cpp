#include <iostream>

#include "api/sdl/SDLInitiator.h"
#include "api/sdl/errors/SDLError.h"
#include "api/sdl/window/Window.h"
#include "engine/rendering/Renderer.h"
#include "engine/drawables/Rect.h"
#include "engine/drawables/Color.h"
#include "engine/drawables/GameObject.h"
#include "engine/math/Vec2.h"
#include "engine/input/EventEmitter.h"
#include "osplatform/ThreadUtils.h"
#include "osplatform/Time.h"

int main() {
  SDLInitiator sdlInit;
  SDLError error;
  if (sdlInit.requireVideo().init() != 0) {
    std::cout << error.getError();
  }
  Window window;
  if (window.init("Test", 640, 480) != 0) {
    std::cout << error.getError();
  }

  Renderer rend;

  if (rend.init(window, Color{}) != 0) {
    std::cout << error.getError();
  }

  Rect rect(100, 100, 100, 100, Color{ 0, 255, 0, 255 });
  GameObject obj(rect, 0, Vec2(0.0f, 0.0f));

  EventEmitter ee;
  bool quit = false;

  ee.listen(Key::ESC, [&quit](Event e) { quit = true; });
  ee.listen(Key::UP, [&obj](Event e) { obj.setSpeed(0.1f); obj.steer(Vec2(0.0f, 1.0f)); });
  ee.listen(Key::DOWN, [&obj](Event e) { obj.setSpeed(0.1f); obj.steer(Vec2(0.0f, -1.0f)); });
  ee.listen(Key::LEFT, [&obj](Event e) { obj.setSpeed(0.1f); obj.steer(Vec2(-1.0f, 0.0f)); });
  ee.listen(Key::RIGHT, [&obj](Event e) { obj.setSpeed(0.1f); obj.steer(Vec2(1.0f, 0.0f)); });

  Time timer;
  float targetFrameRate = 20;
  float frameDurationMs = 1000 / targetFrameRate;

  while (!quit) {
    timer.getElapsed();
    rend.clear();

    ee.poll();

    obj.updatePosition();

    if (rend.render(obj) != 0) {
      std::cout << error.getError();
    }

    rend.update();
    Time stop = timer.getElapsed();
    float timeLeftInFrame = frameDurationMs - stop.toMilliseconds();
    ThreadUtils::sleepFor(timeLeftInFrame);
  }

  return 0;
}
