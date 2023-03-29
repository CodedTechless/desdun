#pragma once

#include <app/input.h>
#include <app/runtime.h>
#include <app/window.h>

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

	using CollisionMap = 
		std::array<std::array<std::vector<PhysicsBody*>, COLLISION_MAP_SIZE>, COLLISION_MAP_SIZE>;

	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		CollisionMap collisionMap;
		Camera* currentCamera = nullptr;

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

			instance->onAwake();

			return instance;
		}

		Vector2 getMouseInWorld() const;
		Instance* getRoot() const { return root; };

	private:
		
		Vector2f mousePos = { 0.f, 0.f };
		Instance* root = nullptr;

		List<Instance*> sceneInstances = {};

		friend class Instance;

	};
}
