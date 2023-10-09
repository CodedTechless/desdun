#pragma once

#include <src/resources/resource.hpp>
#include <src/resources/serial/json_stream.h>

#include <src/runtime/runtime.h>

namespace Desdun
{

	class Model : public Resource
	{
	public:
		Model() = default;

		JSONStream& get();

	private:

		JSONStream model = {};
		
		void load() override;
		void unload() override;

		friend class Resource;
	};



}