#pragma once

#include <game_lib.hpp>
#include "item_slot.hpp"

namespace Desdun
{

	class Container : public Serialisable
	{
	public:
		serialisable(Container);

		Container() = default;
		Container(size_t size);

		

		List<ItemSlot>& getContents() { return contents; };

	protected:
		void serialise(JSONObject& object) const override;
		void deserialise(const JSONObject& object) override;

	private:

		List<ItemSlot> contents = {};
	};


}