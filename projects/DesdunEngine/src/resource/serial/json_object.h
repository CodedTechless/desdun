#pragma once

#include <core_lib.hpp>

namespace Desdun
{
	class JSONStream;
	class Serialisable;

	class JSONObject
	{
	public:

		JSONObject(JSONStream* owner, const json& object)
			: m_Owner(owner), m_jsonObject(object) {};

		JSONObject(JSONStream* owner, Serialisable* object);

		template<typename T>
		json::reference operator[](const T& key)
		{
			return m_jsonObject.at("properties")[key];
		}

		template<typename T>
		json::const_reference operator[](const T& key) const
		{
			return m_jsonObject.at("properties")[key];
		}

		template<typename T>
		json::reference at(const T& key)
		{
			return m_jsonObject.at("properties").at(key);
		}

		template<typename T>
		json::const_reference at(const T& key) const
		{
			return m_jsonObject.at("properties").at(key);
		}

		Serialisable* makeObject();
		uint64_t getReferenceID(Serialisable* pointer) const;
		Serialisable* getPointer(uint64_t reference) const;

		friend void to_json(json& jsonObject, const JSONObject& jsonInst)
		{
			jsonObject = jsonInst.m_jsonObject;
		}

		friend void from_json(const json& jsonObject, JSONObject& jsonInst)
		{
			jsonInst.m_jsonObject = jsonObject;
		}

	private:

		json m_jsonObject = {
			{ "type", nullptr },
			{ "properties", json::object() }
		};

		JSONStream* m_Owner = nullptr;

	};

}