
#include <app/runtime/runtime_info.h>

#include "json_stream.h"
#include "json_object.h"

namespace Desdun
{

	JSONObject::JSONObject(JSONStream* owner, const json& object)
		:m_Owner(owner)
	{

	}

	JSONObject::JSONObject(JSONStream* owner, RuntimeObject* object)
		: m_Owner(owner)
	{
		m_Object["type"] = Runtime::Get(object->GetClassIndex())->GetTypeName();
	}

	uint64_t JSONObject::getReferenceID(RuntimeObject* pointer) const
	{
		return m_Owner->getReferenceFromObject(pointer);
	}

}