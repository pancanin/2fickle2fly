#include "ProgressBar.h"

ProgressBar::ProgressBar(const UITex& texture, uint32_t count): uiTex(texture)
{
	for (size_t i = 0; i < count; i++) {
		increment();
	}
}

void ProgressBar::increment()
{
	uint32_t xOff = 0;
	if (barItems.size() > 0) {
		UITex& last = barItems[barItems.size() - 1];
		xOff = last.getRect().getX() + last.getRect().getWidth();
	}
	Rect copyRect = uiTex.getRect();
	copyRect.updatePosition(Vec2(xOff, copyRect.getY()));
	UITex copy = uiTex;
	copy.setRect(copyRect);
	barItems.push_back(copy);
}

void ProgressBar::decrement()
{
	barItems.pop_back();
}

const std::vector<UITex>& ProgressBar::elements() const
{
	return barItems;
}
