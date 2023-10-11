#pragma once

#include <resources/resource.hpp>
#include <resources/serial/json_stream.hpp>

#include <runtime/runtime.hpp>

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