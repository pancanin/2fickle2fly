#ifndef API_SDL_SDL_INITIATOR_H
#define API_SDL_SDL_INITIATOR_H

#include <cstdint>

/// <summary>
/// (De)initialisation of SDL system.
/// </summary>
class SDLInitiator {
public:
	SDLInitiator();
	SDLInitiator& requireVideo();
	// audio
	// ...fonts

	int32_t init();

	~SDLInitiator();
private:
	uint32_t video;
};

#endif // !API_SDL_SDL_INITIATOR_H
