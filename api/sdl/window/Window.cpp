#include "Window.h"

#include "SDL_video.h"

int32_t Window::init(const std::string& title, uint32_t w, uint32_t h) {
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		return -1;
	}

	return 0;
}

Window::Window(): window(nullptr) {}

Window::~Window() {
	if (window != nullptr) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}
