#include "Renderer.h"

#include "SDL_render.h"

#include "api/sdl/window/Window.h"
#include "engine/drawables/Rect.h"
#include "engine/drawables/GameObject.h"

Renderer::Renderer() : _renderer(nullptr), clearColor(Color{})
{
}

int32_t Renderer::init(Window& window, const Color& clearColor)
{
  SDL_Renderer* r = SDL_CreateRenderer(window.raw(), -1, SDL_RENDERER_ACCELERATED);
  if (!r) {
    return -1;
  }
  _renderer = r;
  this->clearColor = clearColor;

  return SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
}

int32_t Renderer::render(const Rect& rect) const
{
  Color c = rect.getColor();
  int32_t rdc = SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
  if (rdc != 0) return rdc;
  SDL_FRect sdlRect{ rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight() };
  return SDL_RenderFillRectF(_renderer, &sdlRect);
}

int32_t Renderer::render(const GameObject& obj) const
{
  return render(obj.getRect());
}

void Renderer::update() const
{
  SDL_RenderPresent(_renderer);
}

int32_t Renderer::clear() const
{
  int32_t rdc = SDL_SetRenderDrawColor(_renderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
  if (rdc != 0) return rdc;
  return SDL_RenderClear(_renderer);
}

Renderer::~Renderer()
{
  // We do not care if this fails, because it would mean that we have exited the application, in our use-case.
  SDL_DestroyRenderer(_renderer);
}
