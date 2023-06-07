#pragma once

#include <src/app/resource/resource.hpp>
#include <src/app/resource/serial/json_stream.h>

#include <src/app/runtime/runtime.h>

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