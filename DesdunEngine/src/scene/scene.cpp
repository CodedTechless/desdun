

#include <graphics/renderer.h>

#include "scene.h"

namespace Desdun
{

	Scene::Scene()
	{
		rootInstance = Create<Instance>();
		rootInstance->Name = "gameRoot";
	}

	void Scene::OnGameStep(const float delta)
	{
		for (Object* object : SceneObjects)
		{
			object->LastPosition = object->Position;
			object->LastScale = object->Scale;
			object->LastRotation = object->Rotation;
		}

		for (Instance* instance : SceneInstances)
		{
			if (instance->m_Active == false)
			{
				instance->m_Active = true;
			}

			instance->OnGameStep(delta);
		}
	}

	void Scene::OnFrameUpdate(const float delta)
	{
		if (!CurrentCamera) return;

		Renderer::BeginScene(CurrentCamera->m_RenderCamera, CurrentCamera->GetProjectionTransform());

		for (Instance* instance : SceneInstances)
		{
			if (instance->m_Active)
			{
				instance->OnFrameUpdate(delta);
			}
		}

		Renderer::EndScene();
	}

	Input::Filter Scene::OnInputEvent(InputEvent inputObject, bool processed)
	{
		Input::Filter filter = Input::Filter::Ignore;

		for (Instance* instance : SceneInstances)
		{
			auto res = instance->OnInputEvent(inputObject, processed);
			
			if (res == Input::Filter::Stop)
			{
				filter = res;
				break;
			}
			else if (res == Input::Filter::Continue)
			{
				filter = res;
				processed = true;
			}
		}

		return filter;
	}

	void Scene::OnWindowEvent(WindowEvent windowEvent)
	{
		for (Instance* instance : SceneInstances)
		{
			instance->OnWindowEvent(windowEvent);
		}
	}

}