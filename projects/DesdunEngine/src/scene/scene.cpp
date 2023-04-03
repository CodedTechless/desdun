

#include <graphics/renderer.h>
#include <graphics/primitive.h>

#include <object/instance.h>
#include <object/object.h>
#include <object/visual/camera.hpp>
#include <object/physics/physics_body.hpp>

#include <imgui/imgui.h>

#include <resource/types/model.h>

#include "scene.h"

namespace Desdun
{

	Scene::Scene()
	{
		sceneInstances.reserve(MAX_INSTANCES);

		root = create<Instance>();
		root->name = "root";
	}

	Instance* Scene::make(Model* model)
	{
		return nullptr;
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
				instance->onFrameUpdate(delta);

				if (instance->isA<PhysicsBody>())
				{
					auto* phys = (PhysicsBody*)instance;

					for (Vector2 cell : phys->getOwnedCells())
					{
						Primitive::drawRect(cell * (float)COLLISION_MAP_CELL_SIZE, Vector2f(COLLISION_MAP_CELL_SIZE), 100.f);
					};
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