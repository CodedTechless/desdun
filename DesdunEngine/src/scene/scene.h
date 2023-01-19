#pragma once

#include <object/instance.h>
#include <object/types/visual/camera.hpp>

#include <resource/types/model.h>

#include <uuid.hpp>
#include <core_lib.hpp>

namespace Desdun
{

	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		Camera* CurrentCamera = nullptr;

		void OnFrameUpdate(const float Delta);
		void OnGameStep(const float Delta);

		Input::Filter OnInputEvent(InputEvent InputObject, bool Processed);
		void OnWindowEvent(WindowEvent windowEvent);

//		Instance* Instantiate(Model* model);

		template<typename T>
		T* Create()
		{
			T* instance = new T();
			instance->m_ActiveScene = this;
			instance->m_ID = UUID::Generate();

			SceneInstances.push_back((Instance*)instance);

			if (Runtime::Get<T>()->IsA<Object>())
			{
				SceneObjects.push_back((Object*)instance);
			}

			instance->OnAwake();

			return instance;
		}

		Instance* getRoot() const { return rootInstance; };

	private:

		Instance* rootInstance = nullptr;

		std::vector<Instance*> SceneInstances = {};
		std::vector<Object*> SceneObjects = {};

	};

}