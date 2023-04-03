

#include "player.hpp"

namespace Desdun
{
	void Player::onAwake()
	{
		interpolate = true;

		name = "Player";

		auto* legs = getScene()->create<AnimatedSprite>();
		legs->name = "legs";
		legs->setAnimationTable(Resource::fetch<AnimationTable>("animations:player/player_legs.json"));
		legs->interpolate = true;
		legs->setPosition(Vector2(0.f, -16.f));
		legs->zIndex = 10.f;
		legs->setParent(this);

		auto* torso = getScene()->create<AnimatedSprite>();
		torso->name = "torso";
		torso->setAnimationTable(Resource::fetch<AnimationTable>("animations:player/player_torso.json"));
		torso->interpolate = true;
		torso->setPosition(Vector2(0.f, -16.f));
		torso->zIndex = 10.f;
		torso->setParent(this);

		auto* leftEye = getScene()->create<AnimatedSprite>();
		leftEye->name = "leftEye";
		leftEye->setAnimationTable(Resource::fetch<AnimationTable>("animations:player/player_eye.json"));
		leftEye->interpolate = false;
		leftEye->setPosition(Vector2(3.f, -15.f));
		leftEye->setScale(Vector2(-1.f, 1.f));
		leftEye->zIndex = 11.f;
		leftEye->setParent(torso);

		auto* rightEye = getScene()->create<AnimatedSprite>();
		rightEye->name = "rightEye";
		rightEye->setAnimationTable(Resource::fetch<AnimationTable>("animations:player/player_eye.json"));
		rightEye->interpolate = false;
		rightEye->setPosition(Vector2(-3.f, -5.f));
		rightEye->zIndex = 11.f;
		rightEye->setParent(torso);

		auto* shoulders = getScene()->create<WorldObject>();
		shoulders->name = "shoulders";
		shoulders->setParent(torso);

		auto* leftHand = getScene()->create<Sprite>();
		leftHand->name = "leftHand";
		leftHand->image = Resource::fetch<Image>("textures:actors/hand.png");
		leftHand->setPosition(Vector2(16.f, 0.f));
		leftHand->interpolate = false;
		leftHand->zIndex = 10.f;
		leftHand->setParent(shoulders);

		auto* rightHand = getScene()->create<Sprite>();
		rightHand->name = "rightHand";
		rightHand->image = Resource::fetch<Image>("textures:actors/hand.png");
		rightHand->setPosition(Vector2(-16.f, 0.f));
		rightHand->interpolate = false;
		rightHand->zIndex = 10.f;
		rightHand->setParent(shoulders);

		bodyController.start();



	};

	void Player::onInputEvent(Input::Event& event)
	{
		if (event.isPressed(Input::KeyCode::G))
		{
			Debug::Log("kowabunga!");
			saveToFile("models:player.json");
			auto* testLoad = Resource::fetch<Model>("models:player.json");
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