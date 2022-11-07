#pragma once

#include <resource/resource.hpp>

namespace Desdun
{

	class Model : public Resource
	{
	public:
		Model() = default;

		void Load(const std::string& path);

	private:

		static Object* Deconstruct(ByteFile& stream);
	};



}