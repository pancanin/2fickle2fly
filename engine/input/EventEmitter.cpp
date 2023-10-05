#include "EventEmitter.h"

#include "SDL_events.h"

ActionType convertToInternalActionType(SDL_EventType t) {
	if (t == SDL_EventType::SDL_KEYDOWN) {
		return ActionType::KEYDOWN;
	}
	else if (t == SDL_EventType::SDL_KEYUP) {
		return ActionType::KEYUP;
	}
}

void EventEmitter::poll()
{
	SDL_Event e{};
	if (SDL_PollEvent(&e) != 0) {
		ActionType type = convertToInternalActionType(static_cast<SDL_EventType>(e.type));
		for (const KeyBinding& binding : bindings) {
			if (e.key.keysym.sym == static_cast<uint32_t>(binding.key) && binding.action == type) {
				if (binding.action == ActionType::KEYUP) {
					if (binding.key == previousKey) {
						// The key up action is after a key down, no interleaving actions happened.
						binding.listener(Event{});
					}
				}
				else {
					binding.listener(Event{});
				}
			}
		}

		previousKey = static_cast<Key>(e.key.keysym.sym);
	}
}

void EventEmitter::listen(Key k, ActionType t, ListenerFunc l)
{
	bindings.push_back(KeyBinding{k, t, l});
}
