

#include "Instance.h"

namespace Desdun
{
	
	Instance::Instance(Game* game, const std::string& id)
		: GameModel(game), ID(id) {};

	Instance::~Instance()
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

	void Instance::RemoveChild(Instance* instance)
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

	Instance* Instance::FindChild(const std::string& name)
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

	void Instance::SetParent(Instance* instance)
	{
		if (Parent) Parent->RemoveChild(this);

		Parent = instance;

		Parent->Children.push_back(this);
	};

}
