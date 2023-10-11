
#include "serial_object.hpp"


namespace Desdun
{
	const String Serialisable::getClassName() const
	{
		return "Serialisable";
	}

	Type Serialisable::getClassIndex() const
	{
		return typeid(Serialisable);
	};
}