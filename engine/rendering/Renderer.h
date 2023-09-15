#ifndef ENGINE_RENDERING_RENDERER_H
#define ENGINE_RENDERING_RENDERER_H

#include "SDL_pixels.h"

#include "engine/drawables/Color.h"

class Rect;
class Window;

struct SDL_Renderer;

class Renderer {
public:
	Renderer();
	~Renderer();

	int32_t init(Window&, Color& clearColor);
	int32_t render(const Rect&) const;
	void update() const;
	int32_t clear() const;
private:
	SDL_Renderer* _renderer;
	SDL_Color clearColor;
};

#endif // !ENGINE_RENDERING_RENDERER_H
