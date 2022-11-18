#pragma once

/*
	one big index containing every single object type in the game
*/

#include "instance.h"
#include "types/object.h"

// Audio

#include "types/audio/sound.hpp"

// Physics

#include "types/physics/kinematic_body.hpp"
#include "types/physics/static_body.hpp"
#include "types/physics/dynamic_body.hpp"

// Visual

#include "types/visual/animator.hpp"
#include "types/visual/camera.hpp"
#include "types/visual/light.hpp"
#include "types/visual/particle_emitter.hpp"
#include "types/visual/sprite.hpp"
#include "types/visual/tile_map.hpp"

/*
	GAME OBJECTS
*/

#include "game/actors/actor.hpp"


#define TYPENAME(T) { typeid(T), #T }
#define CONSTRUCTOR(T) { #T, []() -> Object* { return new T(); } }

namespace Desdun
{

	/*
	we really need to build runtime information on instance types because without them
	the engine can't discern the difference between different objects!!
	*/

	static std::unordered_map<std::type_index, std::string> RuntimeTypes = {
		TYPENAME(Object),

		TYPENAME(Sound),

		TYPENAME(KinematicBody),
		TYPENAME(StaticBody),
		TYPENAME(DynamicBody),

		TYPENAME(Animator),
		TYPENAME(Camera),
		TYPENAME(Light),

		TYPENAME(ParticleEmitter),
		TYPENAME(Sprite),
		TYPENAME(TileMap),

		TYPENAME(Actor)
	};

	/*
	allows us to build a class type based on its string name
	*/

	static std::unordered_map<std::string, std::function<Object*()>> RuntimeConstructor = {
		CONSTRUCTOR(Object),

		CONSTRUCTOR(Sound),

		CONSTRUCTOR(KinematicBody),
		CONSTRUCTOR(StaticBody),
		CONSTRUCTOR(DynamicBody),

		CONSTRUCTOR(Animator),
		CONSTRUCTOR(Camera),
		CONSTRUCTOR(Light),

		CONSTRUCTOR(ParticleEmitter),
		CONSTRUCTOR(Sprite),
		CONSTRUCTOR(TileMap),

		CONSTRUCTOR(Actor)
	};

	struct RuntimeObject
	{

	};

}