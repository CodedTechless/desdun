#pragma once

/*
one big index containing every single object in the engine
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