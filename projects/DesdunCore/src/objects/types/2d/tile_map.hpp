#pragma once

#include <objects/types/2d/entity.hpp>

namespace DesdunCore
{
	class TileMap : public Entity2D
	{
	public:
		dd_serialisable(TileMap)
	};
}