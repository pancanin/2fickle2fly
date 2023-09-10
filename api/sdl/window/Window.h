#ifndef SDL_COMPONENTS_WINDOW_H_
#define SDL_COMPONENTS_WINDOW_H_

#include <string>
#include <cstdint>

struct SDL_Window;

/**
 * Wrapper around SDL_Window.
 * Manages (de)initialization of window.
 */
class Window {
public:
	int32_t init(const std::string& title, uint32_t width, uint32_t height);
	void resize(uint32_t width, uint32_t height) const;

	Window();
	~Window();
private:
	SDL_Window* window;
};

#endif /* SDL_COMPONENTS_WINDOW_H_ */
