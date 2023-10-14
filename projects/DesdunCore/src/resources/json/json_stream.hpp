#pragma once

#include <corelib/core.hpp>

#include "json_object.hpp"

#define JSON_FORMAT 1

namespace DesdunCore
{

	class AlreadyMadeStreamException : public virtual Exception
	{
	public:
		AlreadyMadeStreamException()
			: Exception("Cannot make a stream object that has already been made!") {};
	};


	/*
		26/11/22
		this is just a substitution for whatever i use to solve the same problem in the future
		probably ByteStream but right now that's breaking my brain, so

		02/04/2023
		omg it's been like a billion months but we ain't doing byte stuff any time soon so
		wooee
		on a plane back from cyprus rn gonna be a long flight fellas

		27/04/2023
		gay gay homosexual

		14/10/2023
		i'm gonna keep this but also add binary stream at some point
	*/

	class JSONStream
	{
	public:

		JSONStream() = default;
		~JSONStream();

		void operator<<(std::ifstream& stream);
		void operator>>(std::ofstream& stream);

		void blueprintOf(Serialisable* rootObject);
		Serialisable* makeFrom();

		/*
			gets the ref number of a serialising object
			 - if the object exists, it just returns its reference index
			 - if it doesn't, then it serialises the object and returns the new reference index
		*/
		uint64_t getReferenceFromObject(Serialisable* object);
		Serialisable* getObjectFromReference(uint64_t reference);

		const List<Serialisable*>& getSerialObjects() const;

	private:

		Serialisable* root = nullptr;

		List<JSONObject*> jsonObjects = {};
		List<Serialisable*> serialObjects = {};

		Map<Serialisable*, uint64_t> m_ObjectReferenceIndex = {};
		Map<uint64_t, Serialisable*> m_ReferenceObjectIndex = {};

		void flush();

		uint64_t add(Serialisable* object);
		Serialisable* add(uint64_t reference);

		void emplace(Serialisable* object, uint64_t reference);
	};

}