#include "Window.h"

#include <iostream>

#include "SDL_video.h"

int32_t Window::init(const std::string& title, uint32_t w, uint32_t h) {
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		return -1;
	}

	std::cout << "Window initialised\n";
	return 0;
}

void Window::resize(uint32_t w, uint32_t h) const {
	SDL_SetWindowSize(window, w, h);
}

Window::Window(): window(nullptr) {}

Window::~Window() {
	if (window != nullptr) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	std::cout << "Window destroyed\n";
}
