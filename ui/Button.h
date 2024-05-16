#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <functional>

#include "ui/UITex.h"

class Button {
	Button(const UITex&, std::function<void()> cb);
private:
	UITex uiTex;
	std::function<void()> callback;
};

#endif // !UI_BUTTON_H
