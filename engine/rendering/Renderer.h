#ifndef ENGINE_RENDERING_RENDERER_H
#define ENGINE_RENDERING_RENDERER_H

#include "SDL_pixels.h"

#include "engine/drawables/Color.h"

struct Rect;
struct GameObject;
class Window;

struct SDL_Renderer;

class Renderer {
public:
	Renderer();
	~Renderer();

	int32_t init(Window&, const Color& clearColor);
	int32_t render(const Rect&) const;
	int32_t render(const GameObject&) const;
	void update() const;
	int32_t clear() const;
private:
	SDL_Renderer* _renderer;
	SDL_Color clearColor;
};

#endif // !ENGINE_RENDERING_RENDERER_H
