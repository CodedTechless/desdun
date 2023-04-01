

#include "player.hpp"

namespace Desdun
{
	void Player::onAwake()
	{
		interpolate = true;

		name = "Player";

		auto* legs = getScene()->create<AnimatedSprite>();
		legs->setAnimationTable(Resource::fetch<AnimationTable>("animations:player/player_legs.json"));
		legs->interpolate = true;
		legs->name = "legs";
		legs->position = Vector2(0.f, -16.f);
		legs->zIndex = 10.f;
		legs->setParent(this);

		auto* torso = getScene()->create<AnimatedSprite>();
		torso->setAnimationTable(Resource::fetch<AnimationTable>("animations:player/player_torso.json"));
		torso->interpolate = true;
		torso->name = "torso";
		torso->position = Vector2(0.f, -16.f);
		torso->zIndex = 10.f;
		torso->setParent(this);

		auto* leftEye = getScene()->create<AnimatedSprite>();
		leftEye->setAnimationTable(Resource::fetch<AnimationTable>("animations:player/player_eye.json"));
		leftEye->name = "leftEye";
		leftEye->interpolate = false;
		leftEye->position = Vector2(3.f, -15.f);
		leftEye->scale = Vector2(-1.f, 1.f);
		leftEye->zIndex = 11.f;
		leftEye->setParent(torso);

		auto* rightEye = getScene()->create<AnimatedSprite>();
		rightEye->setAnimationTable(Resource::fetch<AnimationTable>("animations:player/player_eye.json"));
		rightEye->interpolate = false;
		rightEye->name = "rightEye";
		rightEye->position = Vector2(-3.f, -5.f);
		rightEye->zIndex = 11.f;
		rightEye->setParent(torso);

		bodyController.start();
	};

	void Player::onInputEvent(Input::Event& event)
	{
		if (event.isPressed(Input::MouseCode::Button0))
		{
			
;		}
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
			bodyController.lookDirection = normalisedMovement;
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