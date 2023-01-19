#pragma once

#include <core_lib.hpp>

namespace Desdun
{
	class JSONStream;
	class RuntimeObject;

	class JSONObject
	{
	public:

		JSONObject(JSONStream* owner, const json& object);
		JSONObject(JSONStream* owner, RuntimeObject* object);

		template<typename T>
		json::reference operator[](const T& key)
		{
			return m_Object.at("properties")[key];
		}

		template<typename T>
		json::const_reference operator[](const T& key) const
		{
			return m_Object.at("properties")[key];
		}

		template<typename T>
		json::reference at(const T& key)
		{
			return m_Object.at("properties").at(key);
		}

		template<typename T>
		json::const_reference at(const T& key) const
		{
			return m_Object.at("properties").at(key);
		}

		RuntimeObject* getPointer(uint64_t referenceId) const;
		uint64_t getReferenceID(RuntimeObject* pointer) const;

		friend void to_json(json& jsonObject, const JSONObject& jsonInst)
		{
			jsonObject = jsonInst.m_Object;
		}

		friend void from_json(const json& jsonObject, JSONObject& jsonInst)
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

}