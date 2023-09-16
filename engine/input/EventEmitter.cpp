#include "EventEmitter.h"

#include "SDL_events.h"

void EventEmitter::poll()
{
	SDL_Event e{};
	if (SDL_PollEvent(&e) != 0) {
		for (const KeyBinding& binding : bindings) {
			// For now, key down events should suffice. We might need more complex listening logic - which key and what type of event it is - key up, down etc.
			if (e.key.keysym.sym == static_cast<uint32_t>(binding.key) && e.key.type == SDL_EventType::SDL_KEYDOWN) {
				binding.listener(Event{});
			}
		}
	}
}

void EventEmitter::listen(Key k, ListenerFunc l)
{
	bindings.push_back(KeyBinding{k, l});
}
