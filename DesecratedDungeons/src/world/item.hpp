#pragma once

#include <app/runtime.h>

namespace Desdun
{

	class Item : public Serialisable
	{
	public:
		serialisable(Item);

		std::string id = "";



		void serialise(JSONObject& object) const
		{

		}

		void deserialise(const JSONObject& object)
		{

		}

	};

}