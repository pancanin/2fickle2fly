#include "SDLInitiator.h"

#include "SDL.h"

SDLInitiator::SDLInitiator(): video(0) {}

SDLInitiator& SDLInitiator::requireVideo()
{
  video = SDL_INIT_VIDEO;
  return *this;
}

int32_t SDLInitiator::init()
{
  if (SDL_Init(video) != 0) {
    return -1;
  }
  return 0;
}

SDLInitiator::~SDLInitiator()
{
  // IMG_Quit();
  SDL_Quit();
}
