
#include <app/runtime/runtime_info.h>
#include "json_stream.h"

namespace Desdun
{

	uint64_t JSONStream::getReferenceFromObject(RuntimeObject* object)
	{
		auto it = m_ObjectReferenceIndex.find(object);
		if (it != m_ObjectReferenceIndex.end())
		{
			return it->second;
		}

		return add(object);
	}

	RuntimeObject* JSONStream::getObjectFromReference(uint64_t reference)
	{
		return nullptr;
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
		m_ObjectReferenceIndex[object] = index;
		m_ReferenceObjectIndex[index] = object;

		object->Serialise(newObject);
		return index;
	};
}