

#include <resource/serial/byte_file.h>

#include "model.h"

namespace Desdun
{

	void Model::Load(const std::string& path)
	{
		ByteFile stream(path);

		std::string ClassID = {};
		stream >> ClassID;

		m_Model = Runtime::Get(ClassID)->New();
		m_Model->Deserialise(stream);
	}
}