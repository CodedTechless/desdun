
#include <app/runtime.h>
#include <resource/serial/json_stream.h>

#include "instance.h"

namespace Desdun
{
	Instance::~Instance()
	{
		if (active)
		{
			OnDestroyed();
		}

		for (auto instance : getChildren())
		{
			delete instance;
		}

		if (getParent())
		{
			getParent()->removeChild(this);
		}
	}

	void Instance::saveToFile(const std::string& path) const
	{
		JSONStream stream((Instance*)this);

		std::ofstream filestream(path);
		stream >> filestream;
		
		filestream.close();
	}

	void Instance::serialise(JSONObject& object) const
	{
		object["name"] = name;
		object["Children"] = json::array();

		for (Instance* child : getChildren())
		{
			object["Children"].push_back(object.getReferenceID(child));
		}
	};

	void Instance::deserialise(const JSONObject& object)
	{
		object.at("name").get_to(name);

		for (auto it = object.at("Children").begin(); it != object.at("Children").end(); it++)
		{
			auto reference = it->get<uint64_t>();
			hierarchyTree.m_Container.push_back((Instance*)object.getPointer(reference));
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

	void Instance::removeChild(Instance* instance)
	{
		for (auto it = hierarchyTree.m_Container.begin(); it != hierarchyTree.m_Container.end(); ++it)
		{
			if ((*it)->id == instance->id)
			{
				hierarchyTree.m_Container.erase(it);
				break;
			}
		}
	}

	Instance* Instance::findChild(const std::string& name) const
	{
		for (auto instance : getChildren())
		{
			if (instance->name == name)
			{
				return instance;
			}
		}

		return nullptr;
	}

	void Instance::setParent(Instance* instance)
	{
		if (getParent())
		{
			getParent()->removeChild(this);
		}

		hierarchyTree.m_Parent = instance;

		hierarchyTree.m_Parent->hierarchyTree.m_Container.push_back(this);
	};
}