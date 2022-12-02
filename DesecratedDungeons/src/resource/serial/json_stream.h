#pragma once

#include <app/runtime/runtime_info.h>
#include <libraries.hpp>

#define JSON_FORMAT 1

namespace Desdun
{

	/*
		26/11/22
		this is just a substitution for whatever i use to solve the same problem in the future
		probably ByteStream but right now that's breaking my brain, so
	*/

	class JSONStream;

	class JSONObject
	{
	public:
		
		JSONObject(JSONStream* owner, RuntimeObject* index)
			: m_Owner(owner)
		{
			m_Object["type"] = Runtime::Get(index->GetClassIndex())->GetTypeName();
		}

		json operator[](const std::string& value) const
		{
			return m_Object.at("properties").at(value);
		}

		uint64_t getReferenceID(RuntimeObject* pointer) const
		{
			return m_Owner->getObjectReference(pointer);
		}

		inline friend void to_json(json& jsonObject, const JSONObject& jsonInst)
		{
			jsonObject = jsonInst.m_Object;
		}

		inline friend void from_json(const json& jsonObject, JSONObject& jsonInst)
		{
			jsonInst.m_Object = jsonObject;
		}

	private:

		json m_Object = {
			{ "type", nullptr },
			{ "properties", json::object() }
		};

		JSONStream* m_Owner = nullptr;

	};

	class JSONStream
	{
	public:

		template<typename T>
		JSONStream(T* object)
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

			jsonObject >> stream;
		};

		/*
			gets the ref number of a serialising object
			 - if the object exists, it just returns its reference index
			 - if it doesn't, then it serialises the object and returns the new reference index
		*/
		uint64_t getObjectReference(RuntimeObject* object);

	private:

		uint64_t add(RuntimeObject* object);

		std::vector<JSONObject> m_ObjectArray = {};
		std::unordered_map<void*, uint64_t> m_ObjectIndex = {};
	};

}