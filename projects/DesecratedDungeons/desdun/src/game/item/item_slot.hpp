#pragma once

#include <desdun_engine/desdun_engine.hpp>

namespace Desdun
{

	struct ItemSlot : public Serialisable
	{
	public:
		serialisable(ItemSlot)

		String itemId = "";
		uint quantity = 0;

	protected:
		void serialise(JSONObject& object) const override 
		{
			object["itemId"] = itemId;
			object["quantity"] = quantity;
		};

		void deserialise(const JSONObject& object) override
		{
			object.at("itemId").get_to(itemId);
			object.at("quantity").get_to(quantity);
		};
	};

}