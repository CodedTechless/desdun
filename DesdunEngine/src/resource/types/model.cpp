

#include <resource/serial/json_stream.h>

#include "model.h"

namespace Desdun
{

	void Model::Load(const std::string& path)
	{
#if 0
		ByteFile stream(path);

		std::string ClassID = {};
		stream >> ClassID;

		m_Model = Runtime::Get(ClassID)->New();
		m_Model->Deserialise(stream);
#endif

		json jsonObject;

		std::ifstream filestream(path);
		filestream >> jsonObject;

		JSONStream stream(jsonObject);
		modelObject = stream.getRoot();
	}
}