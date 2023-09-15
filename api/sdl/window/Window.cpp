#include "Window.h"

#include "SDL_video.h"

int32_t Window::init(const std::string& title, uint32_t w, uint32_t h) {
	_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

	if (_window == nullptr) {
		return -1;
	}

	return 0;
}

SDL_Window* Window::raw()
{
	return _window;
}

Window::Window(): _window(nullptr) {}

Window::~Window() {
	SDL_DestroyWindow(_window);
}
