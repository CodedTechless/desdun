#pragma once

#include <resource/resource.hpp>

#include <object/types/object.h>

namespace Desdun
{

	class Model : public Resource
	{
	public:
		Model() = default;

		void Load(const std::string& path);

	private:

		Object* m_ModelObject = nullptr;
	};



}