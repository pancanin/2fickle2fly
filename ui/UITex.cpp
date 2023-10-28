#include "UITex.h"

UITex::UITex(const Texture& tex, const Rect& rect): texture(tex), rect(rect)
{
}

const Texture& UITex::getTexture() const
{
  return texture;
}

const Rect& UITex::getRect() const
{
  return rect;
}

void UITex::setRect(const Rect& r)
{
  this->rect = r;
}
