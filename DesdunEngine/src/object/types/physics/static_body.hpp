#pragma once

#include "physics_body.hpp"

namespace Desdun
{

	/*
		the StaticBody class doesn't do outward collision detection at all,
		it will completely exclude the process of checking for collisions around it.
		this only acts as an anchor point for a collision shape, so that DynamicBody
		objects can collide with it.
	*/
	class StaticBody : public PhysicsBody
	{
	public:
		RUNTIME_CLASS_DEF(StaticBody);

		void onAwake() override
		{
			
		}

		void onDestroyed() override
		{

		}

	private:

		void updateBounds()
		{

		}

	};
}

