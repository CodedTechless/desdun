

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
		rootInstance->name = "gameRoot";
	}

	Instance* Scene::instantiate(Model* model)
	{
		return nullptr;
	}

	Vector2 Scene::getMouseInWorld() const
	{
		Vector2 windowSize = Application::get()->getPrimaryWindow()->getSize();
		Vector2 orthoSize = currentCamera->getRenderCamera().GetOrthoSize();

		Vector2 scaleFactor = orthoSize / windowSize;

		Vector2 cameraPos = currentCamera->getInterpPosition() - (orthoSize / 2.f);
		Vector2 mousePos = Input::getMousePosition();

		return cameraPos + mousePos * scaleFactor;
	}

	void Scene::onGameStep(const float delta)
	{
		for (Object* object : sceneObjects)
		{
			object->LastPosition = object->position;
			object->LastScale = object->scale;
			object->LastRotation = object->rotation;
		}

		for (Instance* instance : sceneInstances)
		{
			if (instance->active == false)
			{
				instance->active = true;
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
			if (instance->active)
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