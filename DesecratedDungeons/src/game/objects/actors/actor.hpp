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

			Sprite* sprite = getScene()->create<Sprite>();
			sprite->name = "Body";

			sprite->image = Resource::Fetch<Image>("assets/textures/skube_idle_right.png");
			sprite->position = Vector2(0.f, -16.f);
			sprite->zIndex = 10.f;
			sprite->setParent(this);

			//sprite->SpriteImage = Resource::Fetch<Image>("assets/textures/white.png");

			saveToFile("assets/models/hello.res");

			Resource::Fetch<Model>("assets/models/hello.res");
		};

		void takeDamage(float amount)
		{

		};

		void serialise(JSONObject& object) const override
		{
			object["health"] = health;
			object["maxHealth"] = maxHealth;

			Object::serialise(object);
		}

		void deserialise(const JSONObject& object) override
		{
			object.at("health").get_to(health);
			object.at("maxHealth").get_to(maxHealth);

			Object::deserialise(object);
		}

	};
}