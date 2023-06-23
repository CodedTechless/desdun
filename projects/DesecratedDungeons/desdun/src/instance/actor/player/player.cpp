
#include <desdun/src/instance/body/humanoid_body.hpp>

#include "player.hpp"

namespace Desdun
{
	void Player::onAwake()
	{
		auto* body = this->getScene()->create<HumanoidBodyController>();
		body->setParent(this);
		body->name = "BodyController";
		body->setupBody();
	};

	void Player::onInputEvent(Input::Event& event)
	{
		if (event.isPressed(Input::KeyCode::G))
		{
			Debug::Log("kowabunga!");
			auto* newMe = (Player*)this->clone();
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
		this->findChild("BodyController")->as<HumanoidBodyController>()->updateBody();

		Vector2 pos = getGlobalPosition();
		Primitive::drawRect(pos, { 1.f, 1.f }, 100.f, 0.f, { 1.f, 0.f, 0.f, 0.2f });
		Primitive::drawLine({ 0.f, 0.f }, { 256.f, 256.f }, { 1.f, 0.f, 0.f, 1.f });
	}

	void Player::onGameStep(float delta)
	{
		auto* body = this->findChild("BodyController")->as<HumanoidBodyController>();

		Vector2 movement = Vector2{
			(float)Input::keyDown(Input::KeyCode::D) - (float)Input::keyDown(Input::KeyCode::A),
			(float)Input::keyDown(Input::KeyCode::S) - (float)Input::keyDown(Input::KeyCode::W)
		};

		Vector2f normalisedMovement = { 0.f, 0.f };
		if (glm::length(movement) > 0.f)
		{
			normalisedMovement = glm::normalize(movement);
			body->setLookDirection(normalisedMovement);

			body->animateSpeedModifier = glm::length(velocity) / maxVelocity;
		}
		else
		{
			body->animateSpeedModifier = 1.f;
		}

		body->animateFactor = glm::length(normalisedMovement);

		move(normalisedMovement);
		KinematicActor::onGameStep(delta);
	}
}