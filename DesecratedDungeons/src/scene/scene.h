#pragma once

#include <object/instance.h>
#include <object/types/visual/camera.hpp>

#include <resource/types/model.h>

#include <uuid.hpp>
#include <libraries.hpp>



namespace Desdun
{

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		Camera* CurrentCamera = nullptr;

		void OnFrameUpdate(const float Delta);
		void OnGameStep(const float Delta);

		Input::Filter OnInputEvent(InputEvent InputObject, bool Processed);
		void OnWindowEvent(WindowEvent windowEvent);

		Object* Instance(Model* model);

		template<typename T>
		T* CreateObject()
		{
			std::string NewID = UUID::Generate();

			T* NewObject = new T();
			NewObject->m_ActiveScene = this;
			NewObject->ID = NewID;

			Objects[ObjectCount++] = (Object*)NewObject;

			NewObject->OnAwake();

			return NewObject;
		}

		template<typename T>
		T* CloneObject(T* objectToClone)
		{

		};

	private:



		std::array<Instance*, MAX_OBJECTS> SceneInstances = {};
		uint ObjectCount = 0;

	};

}