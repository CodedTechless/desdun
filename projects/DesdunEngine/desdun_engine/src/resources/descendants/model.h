#pragma once

#include <desdun_engine/src/resources/resource.hpp>
#include <desdun_engine/src/resources/serial/json_stream.h>

#include <desdun_engine/src/runtime/runtime.h>

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