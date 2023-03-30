
#include <app/runtime.h>

#include "json_stream.h"
#include "json_object.h"

namespace Desdun
{


	JSONObject::JSONObject(JSONStream* owner, Serialisable* object)
		: m_Owner(owner)
	{
		m_jsonObject["type"] = Runtime::get(object->getClassIndex())->getTypeName();
	}

	uint64_t JSONObject::getReferenceID(Serialisable* pointer) const
	{
		return m_Owner->getReferenceFromObject(pointer);
	}

	Serialisable* JSONObject::getPointer(uint64_t reference) const
	{
		return m_Owner->getObjectFromReference(reference);
	}

	Serialisable* JSONObject::makeObject() const
	{
		std::string typeName = m_jsonObject.at("type").get<std::string>();

		Serialisable* newObject = Runtime::get(typeName)->create();
		newObject->deserialise(*this);

		return newObject;
	}

}