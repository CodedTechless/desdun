#pragma once

#include <game_lib.hpp>

#include <scene/scene.h>

namespace Desdun
{

	class Actor : public Object
	{
	public:
		RUNTIME_CLASS_DEF(Actor);

		float health = 100.f;
		float maxHealth = 100.f;

		void onAwake()
		{

			Sprite* sprite = GetScene()->create<Sprite>();
			sprite->Name = "Body";

			sprite->SpriteImage = Resource::Fetch<Image>("assets/textures/skube_idle_right.png");
			sprite->Position = Vector2(0.f, -16.f);
			sprite->ZIndex = 10.f;
			sprite->setParent(this);

			//sprite->SpriteImage = Resource::Fetch<Image>("assets/textures/white.png");

			SaveToFile("assets/models/hello.res");

			Resource::Fetch<Model>("assets/models/hello.res");
		};

		void takeDamage(float amount)
		{

		};

		void Serialise(JSONObject& object) const override
		{
			object["health"] = health;
			object["maxHealth"] = maxHealth;

			Object::Serialise(object);
		}

		void Deserialise(const JSONObject& object) override
		{
			object.at("health").get_to(health);
			object.at("maxHealth").get_to(maxHealth);

			Object::Deserialise(object);
		}

	};
}