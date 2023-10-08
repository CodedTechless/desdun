#pragma once

#include <desdun_engine/src/resources/resource.hpp>

namespace Desdun
{
	class Audio : public Resource
	{
	public:

	private:
		void load() override;
		void unload() override;
		
		friend class Resource;
	};
}