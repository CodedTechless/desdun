
#include <runtime/scene/scene.hpp>
#include <runtime/runtime.hpp>
#include <resources/resource.hpp>
#include <resources/json/json_stream.hpp>

#include "object.hpp"

namespace Desdun
{
	Object::~Object()
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

	Object* Object::clone() const
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
			activeScene->add((Object*)instance);
		}

		return (Object*)root;
	}
	
	void Object::markDirty()
	{
		for (auto* child : getChildren())
		{
			child->markDirty();
		}
	}

	void Object::saveToFile(const std::string& path) const
	{
		JSONStream stream;
		stream.blueprintOf((Object*)this);

		std::ofstream filestream(Resource::transformPath(path));
		stream >> filestream;
		
		filestream.close();
	}

	void Object::serialise(JSONObject& object) const
	{
		object["name"] = name;
		object["children"] = json::array();

		for (Object* child : getChildren())
		{
			object["children"].push_back(object.getReferenceID(child));
		}
	};

	void Object::deserialise(const JSONObject& object)
	{
		object.at("name").get_to(name);

		for (auto it = object.at("children").begin(); it != object.at("children").end(); it++)
		{
			auto reference = it->get<uint64_t>();
			auto* instance = (Object*)object.getPointer(reference);
			instance->setParent(this);
		};
	}

	void Object::removeChild(Object* instance)
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

	Object* Object::findChild(const std::string& name) const
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

	void Object::setParent(Object* instance)
	{
		if (getParent())
		{
			getParent()->removeChild(this);
		}

		hierarchyTree.m_Parent = instance;

		hierarchyTree.m_Parent->hierarchyTree.m_Container.push_back(this);
	};
}