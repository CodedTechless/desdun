#pragma once

#include <game_lib.hpp>

namespace Desdun
{

	class Item
	{
	public:

		struct Properties
		{
			uint maxStack = 1;
		};

		Item() = default;
		Item(const Properties& props)
			: properties(props) {};

		Properties properties = {};

	};

}