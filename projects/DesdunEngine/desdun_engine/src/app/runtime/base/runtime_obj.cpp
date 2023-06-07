

#include "runtime_obj.h"

namespace Desdun
{

	BaseRuntimeClass::BaseRuntimeClass(const String& type_name, Type type_index)
		: typeName(type_name), typeIndex(type_index), inheritsFrom({}) 
	{
	};
	
	BaseRuntimeClass::BaseRuntimeClass(const String& type_name, Type type_index, InitList<BaseRuntimeClass*> inherits_from)
		: typeName(type_name), typeIndex(type_index), inheritsFrom(inherits_from) 
	{
	}

	const String BaseRuntimeClass::getName() const
	{
		return typeName;
	}

	Type BaseRuntimeClass::getIndex() const
	{
		return typeIndex;
	}

	const List<BaseRuntimeClass*>& BaseRuntimeClass::getParents()
	{
		return inheritsFrom;
	}
	
}