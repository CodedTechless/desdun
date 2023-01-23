#pragma once

#include <resource/resource.hpp>

#include <app/runtime.h>

namespace Desdun
{

	class Model : public Resource
	{
	public:
		Model() = default;

		void load(const std::string& path) override;

	private:

		RuntimeObject* modelObject = nullptr;
	};



}