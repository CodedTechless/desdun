

#include <graphics/renderer.h>

#include <object/instance.h>
#include <object/types/object.h>
#include <object/types/visual/camera.hpp>

#include <resource/types/model.h>

#include "scene.h"

namespace Desdun
{

	Scene::Scene()
	{
		rootInstance = create<Instance>();
		rootInstance->Name = "gameRoot";
	}

	Instance* Scene::instantiate(Model* model)
	{
		return nullptr;
	}

	void Scene::onGameStep(const float delta)
	{
		for (Object* object : sceneObjects)
		{
			object->LastPosition = object->Position;
			object->LastScale = object->Scale;
			object->LastRotation = object->Rotation;
		}

		for (Instance* instance : sceneInstances)
		{
			if (instance->m_Active == false)
			{
				instance->m_Active = true;
			}

			instance->onGameStep(delta);
		}
	}

	void Scene::onFrameUpdate(const float delta)
	{
		if (!currentCamera) return;

		Renderer::BeginScene(currentCamera->getRenderCamera(), currentCamera->getProjectionTransform());

		for (Instance* instance : sceneInstances)
		{
			if (instance->m_Active)
			{
				instance->onFrameUpdate(delta);
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