

#include <core/graphics/renderer.h>

#include "scene.h"

namespace Desdun
{

	void Scene::OnGameStep(const float delta)
	{
		for (auto i = Objects.begin(); i < Objects.begin() + ObjectCount; ++i)
		{
			(*i)->OnGameStep(delta);
		}

		for (auto i = Objects.begin(); i < Objects.begin() + ObjectCount; ++i)
		{
			(*i)->LastTransform = (*i)->GoalTransform;
			(*i)->GoalTransform = (*i)->GetTransform();
		}
	}

	void Scene::OnFrameUpdate(const float delta)
	{
		if (!CurrentCamera) return;

		Renderer::BeginScene(CurrentCamera->m_RenderCamera, CurrentCamera->GetProjectionTransform());

		for (auto i = Objects.begin(); i < Objects.begin() + ObjectCount; ++i)
		{
			(*i)->OnFrameUpdate(delta);
		}

		Renderer::EndScene();
	}

	Input::Filter Scene::OnInputEvent(InputEvent inputObject, bool processed)
	{
		Input::Filter filter = Input::Filter::Ignore;

		for (auto i = Objects.begin(); i < Objects.begin() + ObjectCount; ++i)
		{
			auto res = (*i)->OnInputEvent(inputObject, processed);
			
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
			(*i)->OnWindowEvent(windowEvent);
		}
	}

}