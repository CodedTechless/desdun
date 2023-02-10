#pragma once


#include "physics_body.hpp"

namespace Desdun
{

	/*
		same as the StaticBody but it also does outgoing collision checks.
		due to it being expected to change position, it will always do outgoing
		collision checks too, using its grid allocations and hitbox to determine
		what objects it's currently clipping with (either static or dynamic)
	*/
	class DynamicBody : public PhysicsBody
	{
	public:
		RUNTIME_CLASS_DEF(DynamicBody);



		void onAwake() override
		{
			
		}

		void onDestroyed() override
		{

		}

		void onGameStep(float delta)
		{

		}

	};

}
