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
  GameObject obj(rect, .01f, Vec2(1.0f, 0.0f));

  EventEmitter ee;
  bool quit = false;

  ee.listen(Key::ESC, [&quit](Event e) { quit = true; });

  Time timer;
  float targetFrameRate = 30;
  float frameDurationMs = 1000 / targetFrameRate;

  while (!quit) {
    timer.getElapsed();
    rend.clear();

    ee.poll();

    obj.moveAlong();

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
