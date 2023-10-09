
#include <src/runtime/runtime.h>
#include "json_stream.h"

namespace Desdun
{

	JSONStream::~JSONStream()
	{
		for (auto* obj : jsonObjects)
		{
			delete obj;
		}
	}

	uint64_t JSONStream::getReferenceFromObject(Serialisable* object)
	{
		auto it = m_ObjectReferenceIndex.find(object);
		if (it != m_ObjectReferenceIndex.end())
		{
			return it->second;
		}

		return add(object);
	}

	Serialisable* JSONStream::getObjectFromReference(uint64_t reference)
	{
		auto it = m_ReferenceObjectIndex.find(reference);
		if (it != m_ReferenceObjectIndex.end())
		{
			return it->second;
		}

		return add(reference);
	}

	/*
		pushes a new object to the serialised object array
		 - creates a new JSONObject inside of jsonObjects
		 - gets that objects index and inserts it in to the m_ObjectIndex
		 - runs the objects Serialise function (streamT must have Serialise or there's a compile-time error)
	*/
	uint64_t JSONStream::add(Serialisable* object)
	{
		size_t index = jsonObjects.size();

		JSONObject* newObject = new JSONObject(this, object);
		jsonObjects.push_back(newObject);

		emplace(object, index);

		object->serialise(*newObject);
		return index;
	};

	Serialisable* JSONStream::add(uint64_t reference)
	{
		JSONObject* newObject = jsonObjects[reference];
		std::string typeName = newObject->m_jsonObject.at("type").get<std::string>();

		auto* object = Runtime::get(typeName)->create();
		emplace(object, reference);

		object->deserialise(*newObject);
		return object;
	}

	void JSONStream::emplace(Serialisable* object, uint64_t reference)
	{
		m_ReferenceObjectIndex[reference] = object;
		m_ObjectReferenceIndex[object] = reference;

		serialObjects.push_back(object);
	}

	void JSONStream::blueprintOf(Serialisable* object)
	{
		add(object);
		flush();
	};

	void JSONStream::flush()
	{
		// as we're technically remaking the object, clear everything but the JSON data
		root = nullptr;

		m_ReferenceObjectIndex.clear();
		m_ObjectReferenceIndex.clear();
		serialObjects.clear();
	}

	Serialisable* JSONStream::makeFrom()
	{
		flush();

		JSONObject* rootJsonObject = jsonObjects[0];
		root = add((uint64_t)0);

		return root;
	}

	const List<Serialisable*>& JSONStream::getSerialObjects() const
	{
		return serialObjects;
	}

	void JSONStream::operator<<(std::ifstream& stream)
	{
		json jsonObject;
		stream >> jsonObject;

		auto& instances = jsonObject.at("instances");

		for (auto it = instances.begin(); it != instances.end(); ++it)
		{
			jsonObjects.push_back(new JSONObject(this, *it));
		}
	}

	void JSONStream::operator>>(std::ofstream& stream)
	{
		json jsonObject = {
			{ "format", JSON_FORMAT },
			{ "instances", json::array() }
		};

		json& instances = jsonObject["instances"];
		for (auto* jsonObject : jsonObjects)
		{
			instances.push_back(*jsonObject);
		}

		stream << jsonObject;
	};
}