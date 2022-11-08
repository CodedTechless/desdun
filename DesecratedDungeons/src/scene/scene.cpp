

#include <graphics/renderer.h>

#include "scene.h"

namespace Desdun
{

	Object* Scene::Instance(Model* model)
	{
		return nullptr;
	}

	void Scene::OnGameStep(const float delta)
	{
		for (auto i = Objects.begin(); i < Objects.begin() + ObjectCount; ++i)
		{
			Object* object = (*i);

			object->LastPosition = object->Position;
			object->LastScale = object->Scale;
			object->LastRotation = object->Rotation;
		}

		for (auto i = Objects.begin(); i < Objects.begin() + ObjectCount; ++i)
		{
			Object* object = (*i);

			if (object->Active == false)
			{
				object->Active = true;
			}

			object->OnGameStep(delta);
		}
	}

	void Scene::OnFrameUpdate(const float delta)
	{
		if (!CurrentCamera) return;

		Renderer::BeginScene(CurrentCamera->m_RenderCamera, CurrentCamera->GetProjectionTransform());

		for (auto i = Objects.begin(); i < Objects.begin() + ObjectCount; ++i)
		{
			Object* object = (*i);

			if (object->Visible && object->Active)
			{
				object->OnFrameUpdate(delta);
			}
		}

		Renderer::EndScene();
	}

	Input::Filter Scene::OnInputEvent(InputEvent inputObject, bool processed)
	{
		Input::Filter filter = Input::Filter::Ignore;

		for (auto i = Objects.begin(); i < Objects.begin() + ObjectCount; ++i)
		{
			Object* object = (*i);
			auto res = object->OnInputEvent(inputObject, processed);
			
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
		for (auto i = Objects.begin(); i < Objects.begin() + ObjectCount; ++i)
		{
			Object* object = (*i);
			object->OnWindowEvent(windowEvent);
		}
	}

}