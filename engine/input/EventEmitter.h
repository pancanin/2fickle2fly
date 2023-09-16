#ifndef ENGINE_INPUT_EVENT_EMITTER_H
#define ENGINE_INPUT_EVENT_EMITTER_H

#include <functional>
#include <vector>

struct Event {};

typedef std::function<void(Event)> ListenerFunc;

enum class Key {
	ESC = 27
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
