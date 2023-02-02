

#include <graphics/renderer.h>

#include <object/instance.h>
#include <object/types/object.h>
#include <object/types/visual/camera.hpp>

#include <imgui/imgui.h>

#include <resource/types/model.h>

#include "scene.h"

namespace Desdun
{

	Scene::Scene()
	{
		sceneInstances.reserve(8192);
		sceneObjects.reserve(8192);

		rootInstance = create<Instance>();
		rootInstance->name = "gameRoot";
	}

	Instance* Scene::instantiate(Model* model)
	{
		return nullptr;
	}

	Vector2 Scene::getMouseInWorld() const
	{
		return mousePos;
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

		Vector2f windowSize = Application::get()->getPrimaryWindow()->getSize();
		Vector2f orthoSize = currentCamera->renderCamera.getOrthoSize();

		Vector2f cameraPos = currentCamera->position;
		Vector2f mouseRatio = (Input::getMousePosition() / windowSize) - 0.5f;
		mousePos = cameraPos + orthoSize * mouseRatio * currentCamera->scale;
	}

	void Scene::onFrameUpdate(const float delta)
	{
		if (!currentCamera) return;

		Renderer::BeginScene(currentCamera->getProjectionTransform());

		for (Instance* instance : sceneInstances)
		{
			if (instance->active)
			{
				instance->onFrameUpdate(delta);
			}
		}

		//ImGui::Begin("debugger");





		//ImGui::Text(std::string(std::to_string(cameraPos.x) + " " + std::to_string(cameraPos.y)).c_str());
		//ImGui::Text(std::string(std::to_string(mouseRatio.x) + " " + std::to_string(mouseRatio.y)).c_str());
		//ImGui::Text(std::string(std::to_string(mousePos.x) + " " + std::to_string(mousePos.y)).c_str());
		//ImGui::Text(std::string(std::to_string(orthoSize.x) + " " + std::to_string(orthoSize.y)).c_str());
		//ImGui::Text(std::string(std::to_string(currentCamera->scale.x) + " " + std::to_string(currentCamera->scale.y)).c_str());

		//ImGui::End();

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