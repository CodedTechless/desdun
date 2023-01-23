
#include <app/runtime.h>
#include <resource/serial/json_stream.h>

#include "instance.h"

namespace Desdun
{
	Instance::~Instance()
	{
		if (m_Active)
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
		JSONStream stream((Instance*)this);

		std::ofstream filestream(path);
		stream >> filestream;
		
		filestream.close();
	}

	void Instance::Serialise(JSONObject& object) const
	{
		object["Name"] = Name;
		object["Children"] = json::array();

		for (Instance* child : GetChildren())
		{
			object["Children"].push_back(object.getReferenceID(child));
		}
	};

	void Instance::Deserialise(const JSONObject& object)
	{
		object.at("Name").get_to(Name);

		for (auto it = object.at("Children").begin(); it != object.at("Children").end(); it++)
		{
			auto reference = it->get<uint64_t>();
			m_Relation.m_Container.push_back((Instance*)object.getPointer(reference));
		};
	}

#if 0
	void Instance::Serialise(ByteObject& object) const
	{
		object << Name;

		object << GetChildren().size();

		for (Instance* child : GetChildren())
		{
			object << child;
				
				/*Runtime::Get(child->GetClassIndex())->GetTypeName();
			child->Serialise(stream);
		*/}
	}

	void Instance::Deserialise(ByteObject& stream)
	{
		stream >> Name;

		size_t ChildCount;
		stream >> &ChildCount;

		for (size_t i = 0; i < ChildCount; i++)
		{
			std::string ClassID;
			stream >> ClassID;

			Instance* object = Runtime::Get(ClassID)->New();
			m_Relation.m_Container.push_back(object);

			object->Deserialise(stream);
		}
	}
#endif

	void Instance::RemoveChild(Instance* instance)
	{
		for (auto it = m_Relation.m_Container.begin(); it != m_Relation.m_Container.end(); ++it)
		{
			if ((*it)->m_ID == instance->m_ID)
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

	void Instance::setParent(Instance* instance)
	{
		if (GetParent())
		{
			GetParent()->RemoveChild(this);
		}

		m_Relation.m_Parent = instance;

		m_Relation.m_Parent->m_Relation.m_Container.push_back(this);
	};
}