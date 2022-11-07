#pragma once

/*
one big index containing every single object in the engine
*/

/*
	CORE OBJECTS
*/

// Base

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

#define REGISTER_SERIAL(T) if(id == T::ClassID) { return new T(); }

namespace Desdun
{

	Object* Object::CreateClassByID(const int id)
	{
		REGISTER_SERIAL(Object);
		
		// Audio
		
		REGISTER_SERIAL(Sound);

		// Physics

		REGISTER_SERIAL(KinematicBody);
		REGISTER_SERIAL(StaticBody);
		REGISTER_SERIAL(DynamicBody);

		// Visual

		REGISTER_SERIAL(Animator);
		REGISTER_SERIAL(Camera);
		REGISTER_SERIAL(Light);
		REGISTER_SERIAL(ParticleEmitter);
		REGISTER_SERIAL(Sprite);
		REGISTER_SERIAL(TileMap);

		/*
			GAME OBJECTS
		*/

		// Actors

		REGISTER_SERIAL(Actor);
	};

}