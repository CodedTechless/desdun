#pragma once

#include <app/window/input.hpp>
#include <app/window/window.hpp>
#include <runtime/runtime.hpp>

#include <corelib/core.hpp>

namespace Desdun
{

	class Object;
	class Camera2D;
	class Prefab;

	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		Camera2D* currentCamera = nullptr;

		void onFrameUpdate(const float Delta);
		void onGameStep(const float Delta);

		void onInputEvent(Input::Event& event);
		void onWindowEvent(const Window::Event& event);

		Object* instantiate(Prefab* model);

		template<typename T>
		T* create()
		{
			T* instance = new T();
			instance->activeScene = this;
			instance->name = Runtime::get<T>()->getName();
			instance->id = uuid::generate();

			sceneInstances.push_back((Object*)instance);

			return instance;
		}

		Object* getRoot() const { return root; };

	private:
		
		
		Object* root = nullptr;

		List<Object*> sceneInstances = {};

		void add(Object* instance);

		friend class Object;

	};
}
