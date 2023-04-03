

#include <resource/serial/json_stream.h>

#include "model.h"

namespace Desdun
{

	void Model::load()
	{
		std::ifstream filestream(getPath());

		JSONStream stream;
		stream << filestream;
		modelObject = stream.get();
	}

	void Model::unload()
	{
		delete modelObject;
	}
}