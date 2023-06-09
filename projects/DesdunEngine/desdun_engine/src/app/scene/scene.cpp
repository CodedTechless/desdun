

#include <desdun_engine/src/graphics/render/renderer.h>
#include <desdun_engine/src/graphics/primitives/primitive.h>

#include <desdun_engine/src/instance/instance.hpp>
#include <desdun_engine/src/instance/descendants/object.hpp>
#include <desdun_engine/src/instance/descendants/camera.hpp>

#include <desdun_engine/src/app/resource/descendants/model.h>
#include <desdun_engine/src/app/resource/serial/json_stream.h>

#include <desdun_engine/include/imgui/imgui.h>

#include "scene.h"

namespace Desdun
{

	Scene::Scene()
	{
		sceneInstances.reserve(MAX_INSTANCES);

		root = create<Instance>();
		root->name = "root";
	}

	void Scene::add(Instance* instance)
	{
		instance->activeScene = this;
		instance->id = UUID::Generate();

		sceneInstances.push_back((Instance*)instance);
	}

	Instance* Scene::instance(Model* model)
	{
		auto& stream = model->get();
		auto* modelRoot = (Instance*)stream.makeFrom();
		modelRoot->setParent(root);

		for (auto* instance : stream.getSerialObjects())
		{
			add((Instance*)instance);
		}

		return modelRoot;
	}

	Vector2 Scene::getMouseInWorld() const
	{
		return mousePos;
	}

	void Scene::onGameStep(const float delta)
	{
		for (Instance* instance : sceneInstances)
		{
			if (instance->isA<WorldObject>())
			{
				auto* object = (WorldObject*)instance;
				object->ageLocalTransform();
			}
		}

		for (Instance* instance : sceneInstances)
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
			if (instance->isA<WorldObject>())
			{
				auto* object = (WorldObject*)instance;
				object->checkDirty();
			}
		}

		Vector2f windowSize = Application::get()->getPrimaryWindow()->getSize();
		Vector2f orthoSize = currentCamera->renderCamera.getOrthoSize();

		Vector2f cameraPos = currentCamera->position;
		Vector2f mouseRatio = (Input::getMousePosition() / windowSize) - 0.5f;
		mousePos = cameraPos + orthoSize * mouseRatio * currentCamera->scale;
	}

	void Scene::onFrameUpdate(const float delta)
	{
		if (!currentCamera) return;
		
		for (Instance* inst : sceneInstances)
		{
			if (inst->isA<WorldObject>())
			{
				auto* object = (WorldObject*)inst;
				object->markInterpDirty();
			}
		}

		Renderer::BeginScene(currentCamera->getProjectionTransform());

		for (Instance* instance : sceneInstances)
		{
			if (instance->active)
			{
				// TODO: optimise this!! visible should be sorted into its own list
				if (instance->isA<WorldObject>() && instance->as<WorldObject>()->visible == true)
				{
					instance->onFrameUpdate(delta);
				}
			}
		}

		Renderer::EndScene();
	}

	void Scene::onInputEvent(Input::Event& event)
	{
		for (Instance* instance : sceneInstances)
		{
			instance->onInputEvent(event);

			if (event.absorbed)
				break;
		}
	}

	void Scene::onWindowEvent(const Window::Event& windowEvent)
	{
		for (Instance* instance : sceneInstances)
		{
			instance->onWindowEvent(windowEvent);
		}
	}

}