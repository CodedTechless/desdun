#pragma once

#include <resources/resource.hpp>
#include <resources/json/json_stream.hpp>

#include <runtime/runtime.hpp>

namespace Desdun
{

	class Prefab : public Resource
	{
	public:
		Prefab() = default;

		JSONStream& get();

	private:

		JSONStream model = {};
		
		void load() override;
		void unload() override;

		friend class Resource;
	};



}