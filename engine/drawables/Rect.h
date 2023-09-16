#ifndef ENGINE_DRAWABLES_RECT_H
#define ENGINE_DRAWABLES_RECT_H

#include "SDL_rect.h"
#include "Color.h"

struct Rect {
	// TODO: When adding the methods for collision, etc. move this to the cpp file.
	Rect(float x, float y, float w, float h, const Color& c) : _rect(SDL_FRect{ x, y, w, h }), color(c) {}
	SDL_FRect _rect;
	Color color;
};

#endif // !ENGINE_DRAWABLES_RECT_H
