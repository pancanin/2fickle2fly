#ifndef ENGINE_INPUT_EVENT_EMITTER_H
#define ENGINE_INPUT_EVENT_EMITTER_H

#include <functional>
#include <vector>

struct Event {};

typedef std::function<void(Event)> ListenerFunc;

enum class Key {
	ESC = 27,
	UP = 1073741906, //SDLK_UP
	DOWN = 1073741905, //SDLK_DOWN
	LEFT = 1073741904, //SDLK_LEFT
	RIGHT = 1073741903, //SDLF_RIGHT
};

struct KeyBinding {
	Key key;
	ListenerFunc listener;
};

class EventEmitter {
public:
	void poll();
	void listen(Key, ListenerFunc);
private:
	std::vector<KeyBinding> bindings;
};

#endif // !ENGINE_INPUT_EVENT_EMITTER_H
