#include <iostream>

#include "api/sdl/SDLInitiator.h"
#include "api/sdl/errors/SDLError.h"
#include "api/sdl/window/Window.h"
#include "engine/rendering/Renderer.h"
#include "engine/drawables/Rect.h"
#include "engine/drawables/Color.h"
#include "engine/input/EventEmitter.h"

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

  EventEmitter ee;
  bool quit = false;

  ee.listen(Key::ESC, [&quit](Event e) { quit = true; });

  while (!quit) {
    rend.clear();

    ee.poll();

    if (rend.render(rect) != 0) {
      std::cout << error.getError();
    }

    rend.update();
  }

  return 0;
}
