#pragma once

#include <resource/resource.hpp>

namespace Desdun
{
	class Audio : public Resource
	{
	public:
		Audio() = default;
		~Audio();

		void Load(const std::string& path);
	};
}