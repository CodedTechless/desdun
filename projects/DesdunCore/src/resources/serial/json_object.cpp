
#include <runtime/runtime.hpp>

#include "json_stream.hpp"
#include "json_object.hpp"

namespace Desdun
{


	JSONObject::JSONObject(JSONStream* owner, Serialisable* object)
		: m_Owner(owner)
	{
		m_jsonObject["type"] = Runtime::get(object->getClassIndex())->getName();
	}

	uint64_t JSONObject::getReferenceID(Serialisable* pointer) const
	{
		return m_Owner->getReferenceFromObject(pointer);
	}

	Serialisable* JSONObject::getPointer(uint64_t reference) const
	{
		return m_Owner->getObjectFromReference(reference);
	}

}