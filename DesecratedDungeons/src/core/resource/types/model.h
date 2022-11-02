#pragma once

#include <core/resource/resource.hpp>

namespace Desdun
{

	class Model : public Resource
	{
	public:
		Model() = default;

		void Load(const std::string& path);


	};



}