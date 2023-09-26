#ifndef ENGINEV2_GAMEENGINE_H_
#define ENGINEV2_GAMEENGINE_H_

#include <cstdint>

#include "api/sdl/SDLInitiator.h"
#include "engine/rendering/Renderer.h"
#include "api/sdl/window/Window.h"
#include "api/sdl/errors/SDLError.h"
#include "engine/misc/ForwardIdGenerator.h"
#include "engine/drawables/GameObject.h"
#include "engine/storage/PrimitivesStorage.h"
#include "engine/input/EventEmitter.h"
#include "engine/physics/collisions/CollisionData.h"

class GameEngine {
public:
  GameEngine();
	virtual ~GameEngine() = default;

	int32_t init(uint32_t w, uint32_t h);
	void start();
	void setTargetFrameRate(uint32_t frameRate);
protected:
	/// <summary>
	/// The returned pointer is already managed - do not free it!
	/// </summary>
	GameObject* add(const GameObject&);

	uint32_t getWindowWidth() const;
	uint32_t getWindowHeight() const;

	virtual void onStart() = 0;
	virtual void setKeyBindings(EventEmitter&) = 0;
	virtual void onUpdate() = 0;
	virtual void handleCollision(const CollisionData&) = 0;
private:
	EventEmitter ee;
	SDLInitiator sdlInit;
	PrimitivesStorage<GameObject> objects;
	Window window;
	Renderer rend;
	ForwardIdGenerator idGen;
	SDLError error;
	bool stop;
	uint32_t frameDurationMs;
	uint32_t width;
	uint32_t height;
};

#endif /* ENGINEV2_GAMEENGINE_H_ */
