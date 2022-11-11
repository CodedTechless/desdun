

#include <resource/serial/byte_file.h>

#include "model.h"

#define TYPE_DECONSTRUCT_BIN(X, V) if (X::GetSerialID() == V) { X* obj = new X(); obj->Deserialise(stream); return obj; };
#define TYPE_CONSTRUCT_BIN(X) X::GetSerialID();

namespace Desdun
{

	void Model::Load(const std::string& path)
	{
		ByteFile stream(path);

		// we read models into memory by first getting the header object and then working
		// down the tree. models are formatted like so, in byte form:
		// [SERIAL ID * 2][Object BASE...][Derived...Final Type]

		std::string ClassID = {};
		stream >> ClassID;

		m_ModelObject = Object::CreateObjectByName(ClassID);
		m_ModelObject->Deserialise(stream);
	}
}