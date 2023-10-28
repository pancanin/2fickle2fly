#ifndef SDL_GRAPHICS_TEXTURE_H_
#define SDL_GRAPHICS_TEXTURE_H_

#include <iostream>
#include <string>
#include <memory>

#include "engine/math/Vec2.h"
#include "engine/drawables/Rect.h"
#include "engine/misc/ID.h"
#include "engine/rendering/Renderer.h"
#include "engine/misc/Identifiable.h"

#include "SDL_render.h"
#include "SDL_image.h"

struct SDL_Texture;
class Renderer;

struct SDL_TexturePimpl {
	SDL_Texture* t;
};

class Texture : public Identifiable {
public:
	Texture() = default;
	// Calculates width and height of the texture, so textures dimensions have to match the rectangle they will be fitted in.
	Texture(SDL_Texture*);

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

	struct Loader {
		static SDL_Texture* load(Renderer& renderer, const std::string& path) {
			return IMG_LoadTexture(renderer.get(), path.c_str());
		}
	};
private:
	Vec2 dim;
	std::shared_ptr <SDL_TexturePimpl> texturePtr;
	float rotation;
	SDL_RendererFlip flip;

	struct SDL_Texture_Deleter {
		void operator()(SDL_TexturePimpl* texture) {
				SDL_DestroyTexture(texture->t);
				std::cout << "Texture destroyed" << std::endl;
		}
	};
};

#endif /* SDL_GRAPHICS_TEXTURE_H_ */
