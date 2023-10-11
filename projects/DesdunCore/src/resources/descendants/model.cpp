


#include "model.hpp"

namespace Desdun
{

	JSONStream& Model::get()
	{
		return model;
	}

	void Model::load()
	{
		std::ifstream filestream(getPath());
		model << filestream;
	}

	void Model::unload()
	{
	}
}