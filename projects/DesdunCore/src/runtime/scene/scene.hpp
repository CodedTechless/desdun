#pragma once

#include <app/window/input.hpp>
#include <app/window/window.hpp>
#include <runtime/runtime.hpp>

#include <corelib/core.hpp>

namespace Desdun
{

	class Object;
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

		Object* instance(Model* model);

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

		Vector2 getMouseInWorld() const;
		Object* getRoot() const { return root; };

	private:
		
		Vector2f mousePos = { 0.f, 0.f };
		Object* root = nullptr;

		List<Object*> sceneInstances = {};

		void add(Object* instance);

		friend class Object;

	};
}
