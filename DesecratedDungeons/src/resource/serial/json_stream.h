#pragma once

#include <libraries.hpp>

#include "json_object.h"

#define JSON_FORMAT 1

namespace Desdun
{

	/*
		26/11/22
		this is just a substitution for whatever i use to solve the same problem in the future
		probably ByteStream but right now that's breaking my brain, so
	*/

	class JSONStream
	{
	public:

		JSONStream(RuntimeObject* object)
		{
			add(object);
		};

		void operator<<(std::ifstream& stream)
		{

		};

		void operator>>(std::ofstream& stream)
		{
			json jsonObject = {
				{ "format", JSON_FORMAT },
				{ "instances", m_ObjectArray }
			};

			stream << jsonObject;
		};

		/*
			gets the ref number of a serialising object
			 - if the object exists, it just returns its reference index
			 - if it doesn't, then it serialises the object and returns the new reference index
		*/
		uint64_t getReferenceFromObject(RuntimeObject* object);
		RuntimeObject* getObjectFromReference(uint64_t reference);

	private:

		uint64_t add(RuntimeObject* object);

		std::vector<JSONObject> m_ObjectArray = {};
		std::unordered_map<void*, uint64_t> m_ObjectIndex = {};
	};

}