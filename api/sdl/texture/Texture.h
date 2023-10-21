#ifndef SDL_GRAPHICS_TEXTURE_H_
#define SDL_GRAPHICS_TEXTURE_H_

#include <string>

#include "engine/math/Vec2.h"
#include "engine/drawables/Rect.h"
#include "engine/misc/ID.h"
#include "engine/rendering/Renderer.h"
#include "engine/misc/Identifiable.h"

#include "SDL_render.h"
#include "SDL_image.h"

struct SDL_Texture;
class Renderer;

class Texture : public Identifiable {
public:
	// Calculates width and height of the texture, so textures dimensions have to match the rectangle they will be fitted in.
	Texture(SDL_Texture*);
	~Texture();

	//void modulateColor(const Color&) const;
	void activateBlend() const;
	void setAlpha(uint8_t value) const;

	/// <summary>
	/// Use negative angles for counterclockwise rotation.
	/// </summary>
	void rotate(double angle);
	void activateHFlip();
	void activateVFlip();
	Vec2 getDimensions() const;
	SDL_Texture* get() const;
private:
	Vec2 dim;
	SDL_Texture* texture;
	float rotation;
	SDL_RendererFlip flip;
};

class TextureLoader {
	static const SDL_Texture* load(Renderer& renderer, const std::string& path) {
		return IMG_LoadTexture(renderer.get(), path.c_str());
	}
};

#endif /* SDL_GRAPHICS_TEXTURE_H_ */
