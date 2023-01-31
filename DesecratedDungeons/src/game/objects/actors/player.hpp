#pragma once


#include "actor.hpp"


namespace Desdun
{

	class Player : public Actor
	{
	public:
		RUNTIME_CLASS_DEF(Player);

		Vector2 velocity = { 0.f, 0.f };
		float friction = 2000.f;

		float moveAcceleration = 1800.f;
		float maxVelocity = 180.f;

		void onAwake() override
		{

			auto* sprite = getScene()->create<AnimatedSprite>();
			sprite->setSequences({
				{ "idleLeft", Resource::fetch<AnimationSequence>("assets/textures/actors/player/anims/idle_left.json") },
				{ "idleRight", Resource::fetch<AnimationSequence>("assets/textures/actors/player/anims/idle_right.json") },
				{ "idleUp", Resource::fetch<AnimationSequence>("assets/textures/actors/player/anims/idle_up.json") },
				{ "idleDown", Resource::fetch<AnimationSequence>("assets/textures/actors/player/anims/idle_down.json") },

				{ "walkLeft", Resource::fetch<AnimationSequence>("assets/textures/actors/player/anims/walk_left.json") },
				{ "walkRight", Resource::fetch<AnimationSequence>("assets/textures/actors/player/anims/walk_right.json") },
				{ "walkUp", Resource::fetch<AnimationSequence>("assets/textures/actors/player/anims/walk_up.json") },
				{ "walkDown", Resource::fetch<AnimationSequence>("assets/textures/actors/player/anims/walk_down.json") }
			});
			sprite->name = "body";
			sprite->position = Vector2(0, -16);
			sprite->zIndex = -10;
			sprite->setParent(this);

			sprite->play("idleDown");

		};

		void onGameStep(float delta) override
		{
			Vector2 movement = Vector2{
				(float)Input::keyDown(Input::KeyCode::D) - (float)Input::keyDown(Input::KeyCode::A),
				(float)Input::keyDown(Input::KeyCode::S) - (float)Input::keyDown(Input::KeyCode::W)
			};

			Vector2 normalisedMovement = { 0.f, 0.f };
			if (glm::length(movement) > 0.f)
			{
				normalisedMovement = glm::normalize(movement);
			}

			velocity += moveAcceleration * normalisedMovement * delta;

			bool isMoving = glm::length(movement) > 0.f;
			float scalarVelocity = glm::length(velocity);

			if (scalarVelocity > 0.f)
			{
				if (!isMoving)
				{
					scalarVelocity = glm::max(0.f, scalarVelocity - friction * delta);
				}
				else if (scalarVelocity > maxVelocity)
				{
					scalarVelocity = glm::max(maxVelocity, scalarVelocity - friction * delta);
				}

				velocity = glm::normalize(velocity) * scalarVelocity;
			}

			//std::cout << normalisedMovement.x << " " << normalisedMovement.y << " " << velocity.x << " " << velocity.y << std::endl;

			position += velocity * delta;
		}
	};

}