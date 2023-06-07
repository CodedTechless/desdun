
#include "serial_obj.h"


namespace Desdun
{
	Type Serialisable::getClassIndex() const
	{
		return typeid(Serialisable);
	};
}