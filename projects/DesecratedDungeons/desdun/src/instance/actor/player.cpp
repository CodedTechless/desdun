

#include "player.hpp"

namespace Desdun
{
	void Player::onAwake()
	{
		bodyController.start();
	};

	void Player::onInputEvent(Input::Event& event)
	{
		if (event.isPressed(Input::KeyCode::G))
		{
			Debug::Log("kowabunga!");
			auto* newMe = (Player*)clone();
			newMe->setParent(getParent());
			newMe->setPosition({ 0.f, 0.f });
;		}
		else if (event.isPressed(Input::KeyCode::H))
		{
			Debug::Log("boom!");
			saveToFile("models:player.json");
		}
	}

	void Player::onFrameUpdate(float delta)
	{
		bodyController.update();
	}

	void Player::onGameStep(float delta)
	{
		Vector2 movement = Vector2{
			(float)Input::keyDown(Input::KeyCode::D) - (float)Input::keyDown(Input::KeyCode::A),
			(float)Input::keyDown(Input::KeyCode::S) - (float)Input::keyDown(Input::KeyCode::W)
		};

		Vector2f normalisedMovement = { 0.f, 0.f };
		if (glm::length(movement) > 0.f)
		{
			normalisedMovement = glm::normalize(movement);
			bodyController.setLookDirection(normalisedMovement);

			bodyController.animateSpeedModifier = glm::length(moveController.velocity) / moveController.maxVelocity;
		}
		else
		{
			bodyController.animateSpeedModifier = 1.f;
		}

		bodyController.animateFactor = glm::length(normalisedMovement);

		moveController.applyInput(normalisedMovement);
		moveController.step(delta);
	}
}