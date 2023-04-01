#pragma once

#include <resource/resource.hpp>

#include <runtime/runtime.h>

namespace Desdun
{

	class Model : public Resource
	{
	public:
		Model() = default;

		void load(const std::string& path) override;

	private:

		Serialisable* modelObject = nullptr;
	};



}