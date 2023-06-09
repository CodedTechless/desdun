#pragma once

#include <desdun/src/game/actor/move_phys.hpp>
#include <desdun/src/game/model/humanoid_body.hpp>

#include "actor.hpp"

namespace Desdun
{

	class Player : public Actor
	{
	public:
		serialisable(Player);

		MoveController moveController = { this };
		HumanoidBodyController bodyController = { this };

		void onAwake() override;

		void onInputEvent(Input::Event& event) override;

		void onFrameUpdate(float delta) override;
		void onGameStep(float delta) override;

	};

}