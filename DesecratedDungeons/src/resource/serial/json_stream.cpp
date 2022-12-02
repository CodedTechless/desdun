

#include "json_stream.h"

namespace Desdun
{

	uint64_t JSONStream::getObjectReference(RuntimeObject* object)
	{
		auto it = m_ObjectIndex.find(object);
		if (it != m_ObjectIndex.end())
		{
			return it->second;
		}

		return add(object);
	}

	/*
		pushes a new object to the serialised object array
		 - creates a new JSONObject inside of m_ObjectArray
		 - gets that objects index and inserts it in to the m_ObjectIndex
		 - runs the objects Serialise function (streamT must have Serialise or there's a compile-time error)
	*/
	uint64_t JSONStream::add(RuntimeObject* object)
	{
		size_t index = m_ObjectArray.size();
		m_ObjectArray.push_back(JSONObject(this, object));

		JSONObject& newObject = m_ObjectArray[index];
		m_ObjectIndex[object] = index;

		object->Serialise(newObject);
		return index;
	};
}