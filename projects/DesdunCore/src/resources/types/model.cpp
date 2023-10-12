


#include "model.hpp"

namespace Desdun
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