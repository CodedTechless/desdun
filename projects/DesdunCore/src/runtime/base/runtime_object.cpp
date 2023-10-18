

#include "runtime_object.hpp"

namespace DesdunCore
{

	BaseRuntimeClass::BaseRuntimeClass(const String& type_name, Type type_index)
		: typeName(type_name), typeIndex(type_index), inheritsFrom({}) 
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