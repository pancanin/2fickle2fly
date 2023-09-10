#include "SDLError.h"

#include "SDL.h"

const std::string SDLError::getError()
{
  return SDL_GetError();
}
