

#include <graphics/render/renderer.hpp>
#include <graphics/primitives/primitive.hpp>

#include <objects/object.hpp>
#include <objects/types/2d/entity.hpp>
#include <objects/types/2d/camera.hpp>

#include <resources/types/model.hpp>
#include <resources/json/json_stream.hpp>

#include <imgui/imgui.h>

#include "scene.hpp"

namespace Desdun
{

	Scene::Scene()
	{
		sceneInstances.reserve(MAX_INSTANCES);

		root = create<Object>();
		root->name = "root";
	}

	void Scene::add(Object* instance)
	{
		instance->activeScene = this;
		instance->id = uuid::generate();

		sceneInstances.push_back((Object*)instance);
	}

	Object* Scene::instantiate(Prefab* model)
	{
		auto& stream = model->get();
		auto* modelRoot = (Object*)stream.makeFrom();
		modelRoot->setParent(root);

		for (auto* instance : stream.getSerialObjects())
		{
			add((Object*)instance);
		}

		return modelRoot;
	}

	void Scene::onGameStep(const float delta)
	{
		for (Object* instance : sceneInstances)
		{
			if (instance->isA<Entity2D>())
			{
				auto* object = (Entity2D*)instance;
				object->ageLocalTransform();
			}
		}

		for (Object* instance : sceneInstances)
		{
			if (instance->active == false)
			{
				instance->onAwake();
				instance->active = true;
			}

			instance->onGameStep(delta);

			// we may have a problem here
			// what if an object changes another objects position that already got recalculated??
			// then it'd just be wrong...
			if (instance->isA<Entity2D>())
			{
				auto* object = (Entity2D*)instance;
				object->checkDirty();
			}
		}
	}

	void Scene::onFrameUpdate(const float delta)
	{
		if (!currentCamera) return;
		
		for (Object* inst : sceneInstances)
		{
			if (inst->isA<Entity2D>())
			{
				auto* object = (Entity2D*)inst;
				object->markInterpDirty();
			}
		}

		auto* app = Application::get();
		auto* renderer = app->getRenderer();

		renderer->begin(currentCamera->getProjectionTransform());

		for (Object* instance : sceneInstances)
		{
			if (instance->active)
			{
				// TODO: optimise this!! visible should be sorted into its own list
				if (instance->isA<Entity2D>() && instance->as<Entity2D>()->visible == true)
				{
					instance->onFrameUpdate(delta);
				}
			}
		}

		renderer->end();
	}

	void Scene::onInputEvent(Input::Event& event)
	{
		for (Object* instance : sceneInstances)
		{
			instance->onInputEvent(event);

			if (event.absorbed)
				break;
		}
	}

	void Scene::onWindowEvent(const Window::Event& windowEvent)
	{
		for (Object* instance : sceneInstances)
		{
			instance->onWindowEvent(windowEvent);
		}
	}

}