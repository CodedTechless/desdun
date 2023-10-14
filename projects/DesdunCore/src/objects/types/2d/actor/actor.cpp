
#include "actor.hpp"

namespace DesdunCore
{

	void Actor::takeDamage(float amount)
	{

	};

	void Actor::serialise(JSONObject& object) const
	{
		object["health"] = health;
		object["maxHealth"] = maxHealth;

		Entity2D::serialise(object);
	}

	void Actor::deserialise(const JSONObject& object)
	{
		object.at("health").get_to(health);
		object.at("maxHealth").get_to(maxHealth);

		Entity2D::deserialise(object);
	}
}