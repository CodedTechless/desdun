#pragma once

/*
	one big index containing every single object type in the game
*/

#include "object.h"

// Audio

#include "derived/audio/sound.hpp"

// Physics

#include "derived/physics/kinematic_body.hpp"
#include "derived/physics/static_body.hpp"
#include "derived/physics/dynamic_body.hpp"

// Visual

#include "derived/visual/animator.hpp"
#include "derived/visual/camera.hpp"
#include "derived/visual/light.hpp"
#include "derived/visual/particle_emitter.hpp"
#include "derived/visual/sprite.hpp"
#include "derived/visual/tile_map.hpp"

/*
	GAME OBJECTS
*/

#include "game/actors/actor.hpp"


#define TYPENAME(T) { typeid(T), #T }
#define CONSTRUCTOR(T) { #T, []() -> Object* { return new T(); } }

namespace Desdun
{

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

	template<class T>
	std::string GetObjectClassName()
	{
		return RuntimeTypes[typeid(T)];
	}

	Object* Object::CreateObjectByName(const std::string& name)
	{
		return RuntimeConstructor[name]();
	};

}