#include "Texture.h"

Texture::Texture(SDL_Texture* tx):
  texturePtr(std::shared_ptr<SDL_TexturePimpl>(new SDL_TexturePimpl{ tx }, SDL_Texture_Deleter{})),
    dim(Vec2()),
    rotation(0.0),
    flip(SDL_FLIP_NONE) {
  int w, h;
  SDL_QueryTexture(tx, NULL, NULL, &w, &h);
  dim.x = w;
  dim.y = h;
}

//void Texture::modulateColor(const Color& clr) const {
//    SDL_SetTextureColorMod(texture, clr.red, clr.green, clr.blue);
//}

void Texture::activateBlend() const {
	 SDL_SetTextureBlendMode(texturePtr.get()->t, SDL_BLENDMODE_BLEND);
}

void Texture::setAlpha(uint8_t value) const {
	 SDL_SetTextureAlphaMod(texturePtr.get()->t, value);
}

void Texture::rotate(double angle) {
    rotation += angle;
}

void Texture::activateHFlip() {
    flip = SDL_FLIP_HORIZONTAL;
}

void Texture::activateVFlip() {
    flip = SDL_FLIP_VERTICAL;
}

Vec2 Texture::getDimensions() const
{
  return dim;
}

SDL_Texture* Texture::get() const
{
  return texturePtr.get()->t;
}
