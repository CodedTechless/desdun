#pragma once

#include <app/input.h>
#include <app/runtime.h>
#include <app/window.h>

#include <uuid.hpp>
#include <core_lib.hpp>

namespace Desdun
{

	class Camera;
	class Instance;
	class Object;
	class Model;

	class Scene
	{
	public:
		Scene();
		~Scene() = default;


		void onFrameUpdate(const float Delta);
		void onGameStep(const float Delta);

		void onInputEvent(Input::Event& event);
		void onWindowEvent(const Window::Event& event);

		Instance* instantiate(Model* model);

		template<typename T>
		T* create()
		{
			T* instance = new T();
			instance->activeScene = this;
			instance->id = UUID::Generate();

			sceneInstances.push_back((Instance*)instance);

			if (Runtime::Get<T>()->isA<Object>())
			{
				sceneObjects.push_back((Object*)instance);
			}

			instance->onAwake();

			return instance;
		}

		void setCurrentCamera(Camera* camera);

		Instance* getRoot() const { return rootInstance; };
		Camera* getCurrentCamera() const { return currentCamera; };

	private:
		
		Camera* currentCamera = nullptr;
		Instance* rootInstance = nullptr;

		std::vector<Instance*> sceneInstances = {};
		std::vector<Object*> sceneObjects = {};

	};

}