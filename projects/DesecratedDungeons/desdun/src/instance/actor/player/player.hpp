#pragma once

#include <desdun/src/instance/physics/move_phys.hpp>

#include <desdun/src/instance/actor/actor.hpp>

namespace Desdun
{

	class Player : public KinematicActor
	{
	public:
	serialisable(Player)

		void onAwake() override;

		void onInputEvent(Input::Event& event) override;

		void onFrameUpdate(float delta) override;
		void onGameStep(float delta) override;

	};

}