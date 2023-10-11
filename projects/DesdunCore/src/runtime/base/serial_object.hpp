#pragma once

#include <corelib/core.hpp>
#include <resources/serial/json_object.hpp>

namespace Desdun
{

	class Serialisable
	{
	public:
		virtual const String getClassName() const;
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