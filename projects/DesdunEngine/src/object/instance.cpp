
#include <runtime/runtime.h>
#include <resource/resource.hpp>
#include <resource/serial/json_stream.h>

#include "scene/scene.h"

#include "instance.h"

namespace Desdun
{
	Instance::~Instance()
	{
		if (active)
		{
			onDestroyed();
		}

		auto it = std::find(getScene()->sceneInstances.begin(), getScene()->sceneInstances.end(), this);
		if (it != getScene()->sceneInstances.end())
		{
			getScene()->sceneInstances.erase(it);
		}

		if (getParent())
		{
			getParent()->removeChild(this);
		}

		for (auto instance : getChildren())
		{
			delete instance;
		}
	}

	Instance* Instance::clone() const
	{
		if (!activeScene)
		{
			throw NoActiveSceneException(id);
		}

		JSONStream stream;
		stream.blueprintOf((Serialisable*)this);
		
		auto* root = stream.makeFrom();

		for (auto* instance : stream.getSerialObjects())
		{
			activeScene->add((Instance*)instance);
		}

		return (Instance*)root;
	}
	
	void Instance::markDirty()
	{
		for (auto* child : getChildren())
		{
			child->markDirty();
		}
	}

	void Instance::saveToFile(const std::string& path) const
	{
		JSONStream stream;
		stream.blueprintOf((Instance*)this);

		std::ofstream filestream(Resource::transformPath(path));
		stream >> filestream;
		
		filestream.close();
	}

	void Instance::serialise(JSONObject& object) const
	{
		object["name"] = name;
		object["children"] = json::array();

		for (Instance* child : getChildren())
		{
			object["children"].push_back(object.getReferenceID(child));
		}
	};

	void Instance::deserialise(const JSONObject& object)
	{
		object.at("name").get_to(name);

		for (auto it = object.at("children").begin(); it != object.at("children").end(); it++)
		{
			auto reference = it->get<uint64_t>();
			auto* instance = (Instance*)object.getPointer(reference);
			instance->setParent(this);
		};
	}

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