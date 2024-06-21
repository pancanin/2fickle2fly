#include <iostream>

#include "api/sdl/errors/SDLError.h"

#include "games/breakout/Breakout.h"

#undef main

int main() {
  SDLError error;
  Breakout game;

  // The resolution has to be specific for a game, so maybe have a way to set it to the engine from within Breakout class.
  if (game.init("Breakout") != 0) {
    std::cout << error.getError();
    return 1;
  }

  game.start();

  return 0;
}
