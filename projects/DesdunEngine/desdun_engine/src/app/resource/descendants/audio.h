#pragma once

#include <src/app/resource/resource.hpp>

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