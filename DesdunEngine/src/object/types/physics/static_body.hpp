#pragma once

#include "physics_body.hpp"

namespace Desdun
{
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

	};
}

