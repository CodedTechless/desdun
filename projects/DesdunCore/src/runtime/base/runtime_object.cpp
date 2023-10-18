

#include "runtime_object.hpp"

namespace DesdunCore
{

	BaseRuntimeClass::BaseRuntimeClass(const String& type_name, Type type_index)
		: typeName(type_name), typeIndex(type_index), inheritsFrom({}) 
	{
	}

	void BaseRuntimeClass::addParameter(ParameterType type, String name, void* location)
	{

	}

	void BaseRuntimeClass::addMethod(String name, void* location)
	{

	}

	void BaseRuntimeClass::addInheritors(InitList<BaseRuntimeClass*> inheritence)
	{

	};

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