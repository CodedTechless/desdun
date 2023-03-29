#pragma once

#include <core_lib.hpp>

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

		JSONStream() = default;

		JSONStream(Serialisable* rootObject)
		{
			add(rootObject);
		};

		JSONStream(const json& jsonObject)
		{
			auto& instances = jsonObject.at("instances");

			for (auto it = instances.begin(); it != instances.end(); ++it)
			{
				m_ObjectArray.push_back({ this, *it });
			}

			JSONObject& rootJsonObject = m_ObjectArray[0];
			root = rootJsonObject.makeObject();
		}

		void operator<<(std::ifstream& stream)
		{
			json jsonObject;
			stream >> jsonObject;
		}

		void operator>>(std::ofstream& stream)
		{
			json jsonObject = {
				{ "format", JSON_FORMAT },
				{ "instances", m_ObjectArray }
			};

			stream << jsonObject;
		};

		Serialisable* getRoot() const
		{
			return root;
		};

		/*
			gets the ref number of a serialising object
			 - if the object exists, it just returns its reference index
			 - if it doesn't, then it serialises the object and returns the new reference index
		*/
		uint64_t getReferenceFromObject(Serialisable* object);
		Serialisable* getObjectFromReference(uint64_t reference);

	private:

		uint64_t add(Serialisable* object);
		Serialisable* add(uint64_t reference);

		Serialisable* root = nullptr;

		std::vector<JSONObject> m_ObjectArray = {};

		std::unordered_map<Serialisable*, uint64_t> m_ObjectReferenceIndex = {};
		std::unordered_map<uint64_t, Serialisable*> m_ReferenceObjectIndex = {};
	};

}