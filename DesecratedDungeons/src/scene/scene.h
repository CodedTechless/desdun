#pragma once

#include <object/object.h>
#include <object/derived/visual/camera.hpp>

#include <resource/types/model.h>

#include <uuid.hpp>
#include <libraries.hpp>

#define MAX_OBJECTS 4196

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

		

	private:

		std::array<Object*, MAX_OBJECTS> Objects = {};
		uint ObjectCount = 0;

	};

}