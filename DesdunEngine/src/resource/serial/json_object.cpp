
#include <app/runtime.h>

#include "json_stream.h"
#include "json_object.h"

namespace Desdun
{


	JSONObject::JSONObject(JSONStream* owner, RuntimeObject* object)
		: m_Owner(owner)
	{
		m_jsonObject["type"] = Runtime::Get(object->GetClassIndex())->GetTypeName();
	}

	uint64_t JSONObject::getReferenceID(RuntimeObject* pointer) const
	{
		return m_Owner->getReferenceFromObject(pointer);
	}

	RuntimeObject* JSONObject::getPointer(uint64_t reference) const
	{
		return m_Owner->getObjectFromReference(reference);
	}

	RuntimeObject* JSONObject::makeObject() const
	{
		std::string typeName = m_jsonObject.at("type").get<std::string>();

		RuntimeObject* newObject = Runtime::Get(typeName)->New();
		newObject->Deserialise(*this);

		return newObject;
	}

}