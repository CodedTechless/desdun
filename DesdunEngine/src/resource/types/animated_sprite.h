#pragma once

#include <resource/resource.hpp>

namespace Desdun
{
	class AnimatedSprite : public Resource
	{
	public:

		void load(const std::string& path) override;

	};
}

