#include <iostream>

#include "api/sdl/errors/SDLError.h"

#include "games/breakout/Breakout.h"

#undef main

int main() {
  SDLError error;
  Breakout breakout;

  // The resolution has to be specific for a game, so maybe have a way to set it to the engine from within Breakout class.
  if (breakout.init("Breakout") != 0) {
    std::cout << error.getError();
    return 1;
  }
  
  // Game idea: On each hit, play a bit of a song.
  breakout.start();

  return 0;
}
