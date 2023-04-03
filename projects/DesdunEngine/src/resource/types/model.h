#pragma once

#include <resource/resource.hpp>

#include <runtime/runtime.h>

namespace Desdun
{

	class Model : public Resource
	{
	public:
		Model() = default;


	private:

		Serialisable* modelObject = nullptr;
		
		void load() override;
		void unload() override;
	};



}