#pragma once

#include <app/input.h>
#include <app/window.h>
#include <runtime/runtime.h>

#include <uuid.hpp>
#include <core_lib.hpp>

namespace Desdun
{

	class Instance;
	class WorldObject;
	class PhysicsBody;
	class StaticBody;
	class DynamicBody;
	class Camera;
	class Model;

	using HashMap = Map<Vector2i, List<Instance*>>;

	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		HashMap level = {};
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
			instance->id = UUID::Generate();

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
