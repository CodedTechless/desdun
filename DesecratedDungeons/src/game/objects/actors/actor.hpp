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