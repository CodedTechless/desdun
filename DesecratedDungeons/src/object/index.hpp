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

#include <frozen/unordered_map.h>
#include <frozen/string.h>

#define QUERY_TYPE(T) if (GetGlobalClassName<T>() == name) { return new T(); }

namespace Desdun
{

	static std::unordered_map<std::type_index, std::string> RuntimeTypes = {
		{ typeid(Object), "Object" },

		{ typeid(Sound), "Sound" },
		
		{ typeid(KinematicBody), "KinematicBody" },
		{ typeid(StaticBody), "StaticBody" },
		{ typeid(DynamicBody), "DynamicBody" },

		{ typeid(Animator), "Animator" },
		{ typeid(Camera), "Camera" },
		{ typeid(Light), "Light" },

		{ typeid(ParticleEmitter), "ParticleEmitter" },
		{ typeid(Sprite), "Sprite" },
		{ typeid(TileMap), "TileMap" },

		{ typeid(Actor), "Actor" }
	};

	template<class T>
	std::string GetGlobalClassName()
	{
		return RuntimeTypes[typeid(T)];
	}

	Object* Object::CreateClassByName(const std::string& name)
	{
		QUERY_TYPE(Object);
		
		// Audio
		
		QUERY_TYPE(Sound);

		// Physics

		QUERY_TYPE(KinematicBody);
		QUERY_TYPE(StaticBody);
		QUERY_TYPE(DynamicBody);

		// Visual

		QUERY_TYPE(Animator);
		QUERY_TYPE(Camera);
		QUERY_TYPE(Light);
		QUERY_TYPE(ParticleEmitter);
		QUERY_TYPE(Sprite);
		QUERY_TYPE(TileMap);

		/*
			GAME OBJECTS
		*/

		// Actors

		QUERY_TYPE(Actor);
	};

}