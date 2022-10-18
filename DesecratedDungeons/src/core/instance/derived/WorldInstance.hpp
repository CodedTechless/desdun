#pragma once

#include <core/instance/base/Instance.h>

using namespace Desdun;

// Instance > WorldInstance

namespace Enum
{
	enum class InterpolationMode
	{
		Enabled = 0,
		Inherited = 1,
		Disabled = 2
	};
}

class WorldInstance : public Instance
{
public:
	WorldInstance() = default;

	Vector2 Position = {};
	int ZIndex = 0;

	Enum::InterpolationMode Mode = Enum::InterpolationMode::Enabled;

};