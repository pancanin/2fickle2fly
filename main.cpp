#include <iostream>

#include "api/sdl/errors/SDLError.h"

#include "games/breakout/Breakout.h"

int main() {
  SDLError error;
  Breakout breakout;
  if (breakout.init() != 0) {
    std::cout << error.getError();
    return 1;
  }
  
  breakout.start();

  return 0;
}
