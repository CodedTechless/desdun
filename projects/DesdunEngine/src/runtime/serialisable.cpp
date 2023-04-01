
#include "serialisable.h"


namespace Desdun
{
	Type Serialisable::getClassIndex() const
	{
		return typeid(Serialisable);
	};
}