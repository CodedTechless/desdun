


#include "model.hpp"

namespace DesdunCore
{

	JSONStream& Prefab::get()
	{
		return model;
	}

	void Prefab::load()
	{
		std::ifstream filestream(getPath());
		model << filestream;
	}

	void Prefab::unload()
	{
	}
}