#pragma once

#include <game/world/actor/move_controller.hpp>
#include <game/world/actor/model/humanoid_body_controller.h>

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