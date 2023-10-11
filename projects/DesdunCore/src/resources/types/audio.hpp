#pragma once

#include <resources/resource.hpp>

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