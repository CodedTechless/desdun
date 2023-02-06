#pragma once


#include "physics_body.hpp"

namespace Desdun
{

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
