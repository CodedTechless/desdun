

#include "object.h"

namespace Desdun
{

	Object::~Object()
	{
		for (auto instance : Children)
		{
			delete instance;
		}

		if (Parent)
		{
			Parent->RemoveChild(this);
		}
	}

	void Object::RemoveChild(Object* instance)
	{
		for (auto it = Children.begin(); it != Children.end(); ++it)
		{
			if ((*it)->ID == instance->ID)
			{
				Children.erase(it);
				break;
			}
		}
	}

	Object* Object::FindChild(const std::string& name)
	{
		for (auto instance : Children)
		{
			if (instance->Name == name)
			{
				return instance;
			}
		}

		return nullptr;
	}

	void Object::SetParent(Object* instance)
	{
		if (Parent) Parent->RemoveChild(this);

		Parent = instance;

		Parent->Children.push_back(this);
	};

}
