#pragma once

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
		
		template<typename T>
		JSONObject(JSONStream* owner, T* object)
			: m_Owner(owner)
		{
			m_Object["type"] = Runtime::Get(object->GetClassIndex())->GetTypeName();
		}

		json operator[](const std::string& value)
		{
			return m_Object.at("properties").at(value);
		}

		template<typename pointerT>
		uint64_t getReferenceID(pointerT* pointer)
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
		template<typename pointerT>
		uint64_t getObjectReference(pointerT* object)
		{
			auto it = m_ObjectIndex.find(object);
			if (it != m_ObjectIndex.end())
			{
				return it->second;
			}

			return add(object);
		}

	private:

		/*
			pushes a new object to the serialised object array
			 - creates a new JSONObject inside of m_ObjectArray
			 - gets that objects index and inserts it in to the m_ObjectIndex
			 - runs the objects Serialise function (streamT must have Serialise or there's a compile-time error)
		*/

		template<typename streamT>
		uint64_t add(streamT* object)
		{
			size_t index = m_ObjectArray.size();
			m_ObjectArray.push_back(JSONObject(this, object));

			JSONObject& newObject = m_ObjectArray[index];
			m_ObjectIndex[object] = index;

			object->Serialise(newObject);
			return index;
		};

		std::vector<JSONObject> m_ObjectArray = {};
		std::unordered_map<void*, uint64_t> m_ObjectIndex = {};
	};

}