#pragma once

#include <resource/resource.hpp>

namespace Desdun
{
	class Audio : public Resource
	{
	public:

	private:
		void load() override;
		void unload() override;
	};
}