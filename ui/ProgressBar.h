#ifndef UI_PROGRESS_BAR_H
#define UI_PROGRESS_BAR_H

#include <cstdint>
#include <vector>

#include "engine/math/Vec2.h"
#include "api/sdl/texture/Texture.h"
#include "ui/UITex.h"
#include "engine/misc/Identifiable.h"

class ProgressBar : public Identifiable {
public:
	ProgressBar(const UITex& texture, uint32_t count);

	void increment();
	void decrement();

	const std::vector<UITex>& elements() const;
private:
	UITex uiTex; // This will be used as a blueprint to clone the progress bar items. Do not modify directly.
	std::vector<UITex> barItems;
};

#endif // !UI_PROGRESS_BAR_H
