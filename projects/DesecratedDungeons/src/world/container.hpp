#pragma once

#include <app/runtime.h>


namespace Desdun
{

	class Container : public Serialisable
	{
	public:
		serialisable(Container);

		Container(size_t size);

		void serialise(JSONObject& object) const override;
		void deserialise(const JSONObject& object) override;
	};


}