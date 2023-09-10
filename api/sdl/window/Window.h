#ifndef SDL_COMPONENTS_WINDOW_H_
#define SDL_COMPONENTS_WINDOW_H_

#include <string>
#include <cstdint>

struct SDL_Window;

/// <summary>
/// Wrapper around SDL_Window.
/// Manages(de)initialization of window.
/// </summary>
class Window {
public:
	int32_t init(const std::string& title, uint32_t w, uint32_t h);

	Window();
	~Window();
private:
	SDL_Window* window;
};

#endif /* SDL_COMPONENTS_WINDOW_H_ */
