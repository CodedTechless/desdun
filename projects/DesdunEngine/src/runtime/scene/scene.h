#pragma once

#include <src/app/window/input.h>
#include <src/app/window/window.h>
#include <src/runtime/runtime.h>

#include <include/ddlib/core.hpp>

namespace Desdun
{

	class Instance;
	class WorldObject;
	class Camera;
	class Model;

	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		Camera* currentCamera = nullptr;

		void onFrameUpdate(const float Delta);
		void onGameStep(const float Delta);

		void onInputEvent(Input::Event& event);
		void onWindowEvent(const Window::Event& event);

		Instance* instance(Model* model);

		template<typename T>
		T* create()
		{
			T* instance = new T();
			instance->activeScene = this;
			instance->name = Runtime::get<T>()->getName();
			instance->id = uuid::generate();

			sceneInstances.push_back((Instance*)instance);

			return instance;
		}

		Vector2 getMouseInWorld() const;
		Instance* getRoot() const { return root; };

	private:
		
		Vector2f mousePos = { 0.f, 0.f };
		Instance* root = nullptr;

		List<Instance*> sceneInstances = {};

		void add(Instance* instance);

		friend class Instance;

	};
}
