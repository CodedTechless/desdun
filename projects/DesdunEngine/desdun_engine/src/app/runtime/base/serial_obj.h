#pragma once

#include <include/desdun_core.hpp>
#include <src/app/resource/serial/json_object.h>

namespace Desdun
{

	class Serialisable
	{
	public:
		virtual Type getClassIndex() const;

		template<typename T>
		T* as() const { return (T*)this; };

	protected:

		virtual void serialise(JSONObject& object) const = 0;
		virtual void deserialise(const JSONObject& object) = 0;

		friend class JSONStream;
		friend class JSONObject;
	};

}