

#include "instance.h"

namespace Desdun
{
	Instance::~Instance()
	{
		if (Active)
		{
			OnDestroyed();
		}

		for (auto instance : GetChildren())
		{
			delete instance;
		}

		if (GetParent())
		{
			GetParent()->RemoveChild(this);
		}
	}

	void Instance::SaveToFile(const std::string& path) const
	{
		ByteFile stream(path);

		stream << GetClassName();

		Serialise(stream);
	}

	void Instance::Serialise(ByteFile& stream) const
	{
		stream << Name;

		stream << GetChildren().size();

		for (Instance* child : GetChildren())
		{
			stream << child->GetClassName();
			child->Serialise(stream);
		}
	}

	void Instance::Deserialise(ByteFile& stream)
	{


		size_t ChildCount;
		stream >> &ChildCount;

		for (size_t i = 0; i < ChildCount; i++)
		{
			std::string ClassID;
			stream >> ClassID;

			Instance* object = CreateObjectByName(ClassID);
			m_Relation.m_Container.push_back(object);

			object->Deserialise(stream);
		}
	}

	void Instance::RemoveChild(Instance* instance)
	{
		for (auto it = m_Relation.m_Container.begin(); it != m_Relation.m_Container.end(); ++it)
		{
			if ((*it)->ID == instance->ID)
			{
				m_Relation.m_Container.erase(it);
				break;
			}
		}
	}

	Instance* Instance::FindChild(const std::string& name) const
	{
		for (auto instance : GetChildren())
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
		if (GetParent())
		{
			GetParent()->RemoveChild(this);
		}

		m_Relation.m_Parent = instance;

		m_Relation.m_Parent->m_Relation.m_Container.push_back(this);
	};
}