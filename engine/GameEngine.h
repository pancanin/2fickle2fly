#ifndef ENGINEV2_GAMEENGINE_H_
#define ENGINEV2_GAMEENGINE_H_

#include <cstdint>
#include <string>

#include "api/sdl/SDLInitiator.h"
#include "engine/rendering/Renderer.h"
#include "api/sdl/window/Window.h"
#include "api/sdl/errors/SDLError.h"
#include "api/sdl/texture/Texture.h"
#include "engine/misc/ForwardIdGenerator.h"
#include "engine/drawables/GameObject.h"
#include "engine/storage/PrimitivesStorage.h"
#include "engine/input/EventEmitter.h"
#include "engine/physics/collisions/CollisionData.h"
#include "engine/physics/collisions/CollisionDetector.h"
#include "engine/physics/collisions/CollisionAggregator.h"
#include "engine/physics/collisions/CollisionResolver.h"

class CollisionResolver;
class CollisionDetector;

class GameEngine {
public:
	GameEngine(uint32_t w, uint32_t h, uint32_t frameRate);
	virtual ~GameEngine() = default;

	int32_t init(const std::string& windowLabel);
	void start();
protected:
	
	/// <summary>
	/// Important: Add objects that should react first on collision before other objects.
	/// For example, if we have a paddle and a ball, we want to separate the ball first.
	/// This is a temporary measure.
	/// 
	/// Adds a GameObject to storage and assigns it an ID.
	/// </summary>
	/// <param name="obj">Temporary GameObject used for initialising the 'permanent' GameObject that will 'live' in storage.</param>
	/// <returns>The id of the added object. This id can be used for retrieving the object.</returns>
	ID add(const GameObject&);
	ID add(const Texture&);

	uint32_t getWindowWidth() const;
	uint32_t getWindowHeight() const;

	virtual void onStart() = 0;
	virtual void setKeyBindings(EventEmitter&) = 0;
	virtual void onUpdate() = 0;
	virtual void handleCollision(const CollisionData&) = 0;

	// Do not add objects directly. Use the 'add' method of this class to add GameObjects to the game.
	PrimitivesStorage<GameObject> objects;
	PrimitivesStorage<Texture> textures;
private:
	EventEmitter ee;
	SDLInitiator sdlInit;
	Window window;
	Renderer rend;
	ForwardIdGenerator idGen;
	SDLError error;
	bool stop;
	uint32_t frameDurationMs;
	uint32_t width;
	uint32_t height;
	CollisionDetector detector;
	CollisionAggregator aggre;
protected:
	CollisionResolver collisionResolver;
};

#endif /* ENGINEV2_GAMEENGINE_H_ */
