#pragma once

#include <object/instance.h>
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

		uint64_t GetReferenceID(void* pointer)
		{

		}

	private:

		json m_Object = {
			{ "type", "" },
			{ "properties", json::object() }
		};

		JSONStream* m_Owner = nullptr;

	};

	class JSONStream
	{
	public:
		JSONStream() = default;

		void operator<<(std::ifstream& stream)
		{
			m_Object << stream;
		}

		void operator>>(std::ofstream& stream)
		{
			m_Object >> stream;
		}

		/*
			pushes a new object to the serialised object array
			 - creates a new JSONObject inside of m_ObjectArray
			 - gets that objects index and inserts it in to the m_ObjectIndex
			 - runs the objects Serialise function (streamT must have Serialise or there's a compile-time error)
		*/
		template<typename streamT>
		void operator<<(streamT* object)
		{
			size_t index = m_ObjectArray.size();
			m_ObjectArray.push_back(JSONObject(this, object));
			
			JSONObject& newObject = m_ObjectArray[index];
			m_ObjectIndex[object] = index;

			object->Serialise(newObject);
		}

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

			operator<<(object);
			return m_ObjectArray.size() - 1;
		}

	private:

		json m_Object = {
			{ "format", JSON_FORMAT },
			{ "instances", json::array() }
		};

		std::vector<JSONObject> m_ObjectArray = {};
		std::unordered_map<void*, uint64_t> m_ObjectIndex = {};

	};

}