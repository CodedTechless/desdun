
#include <runtime/runtime.h>
#include "json_stream.h"

namespace Desdun
{

	uint64_t JSONStream::getReferenceFromObject(Serialisable* object)
	{
		auto it = m_ObjectReferenceIndex.find(object);
		if (it != m_ObjectReferenceIndex.end())
		{
			return it->second;
		}

		return add(object);
	}

	Serialisable* JSONStream::getObjectFromReference(uint64_t reference)
	{
		auto it = m_ReferenceObjectIndex.find(reference);
		if (it != m_ReferenceObjectIndex.end())
		{
			return it->second;
		}

		return add(reference);
	}

	/*
		pushes a new object to the serialised object array
		 - creates a new JSONObject inside of m_ObjectArray
		 - gets that objects index and inserts it in to the m_ObjectIndex
		 - runs the objects Serialise function (streamT must have Serialise or there's a compile-time error)
	*/
	uint64_t JSONStream::add(Serialisable* object)
	{
		size_t index = m_ObjectArray.size();
		m_ObjectArray.push_back(JSONObject(this, object));

		JSONObject& newObject = m_ObjectArray[index];
		m_ObjectReferenceIndex[object] = index;
		m_ReferenceObjectIndex[index] = object;

		object->serialise(newObject);
		return index;
	};

	Serialisable* JSONStream::add(uint64_t reference)
	{
		Serialisable* newObject = m_ObjectArray[reference].makeObject();
		m_ReferenceObjectIndex[reference] = newObject;
		m_ObjectReferenceIndex[newObject] = reference;

		return newObject;
	}

}