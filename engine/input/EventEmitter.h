#ifndef ENGINE_INPUT_EVENT_EMITTER_H
#define ENGINE_INPUT_EVENT_EMITTER_H

#include <functional>
#include <vector>

struct Event {
};

typedef std::function<void(Event)> ListenerFunc;

enum class Key {
	ESC = 27,
	UP = 1073741906, //SDLK_UP
	DOWN = 1073741905, //SDLK_DOWN
	LEFT = 1073741904, //SDLK_LEFT
	RIGHT = 1073741903, //SDLF_RIGHT
	SPACE = 32, //SDLK_SPACE
};

enum class ActionType {
	KEYUP,
	KEYDOWN
};

struct KeyBinding {
	Key key;
	ActionType action; // The type of key press - pressing the key down, up, holding it, etc.
	ListenerFunc listener;
};

class EventEmitter {
public:
	void poll();
	void listen(Key, ActionType, ListenerFunc);
private:
	std::vector<KeyBinding> bindings;
	Key previousKey;
};

#endif // !ENGINE_INPUT_EVENT_EMITTER_H
