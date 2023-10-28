#ifndef UI_UITEX_H
#define UI_UITEX_H

#include "engine/drawables/Rect.h"
#include "api/sdl/texture/Texture.h"

struct UITex {
	UITex() = default;
	UITex(const Texture&, const Rect&);

	const Texture& getTexture() const;
	const Rect& getRect() const;
	void setRect(const Rect&);
private:
	Texture texture;
	Rect rect;
};

#endif // !UI_UITEX_H
