#pragma once

#include <libraries.hpp>

#include <app/input/input.h>
#include <app/input/event.h>

#include <core/resource/external/image.h>

/*
	Base class of all Objects.
*/

namespace Desdun
{

	class Game;

	class Object
	{
	public:

		Object(Game* game, const std::string& id);
		~Object();
		
		std::string Name = "Object";

		Vector2 Position = { 0.f, 0.f };
		Vector2 Scale = { 0.f, 0.f };
		float Angle = 0.f;

		float ZIndex = 0.f;

		bool Visible = true;

		// Virtuals

		virtual void OnAwake() {};
		virtual void OnDestroyed() {};

		virtual void OnGameStep(const float Delta) {};
		virtual void OnFrameUpdate(const float Delta) {};

		virtual Input::Filter OnInputEvent(InputEvent input, bool processed) { return Input::Filter::Ignore; };
		virtual void OnWindowEvent(WindowEvent window) {};

		// Object operations

		void SetParent(Object* instance);
		Object* FindChild(const std::string& name);

		// Getters

		std::string GetObjectID() const { return ID; };
		Game* GetGameModel() const { return GameModel; };

		const std::vector<Object*>& GetChildren() const { return Children; };
		Object* GetParent() const { return Parent; };
		
		Object* operator[](uint idx)
		{
			return Children[idx];
		}

	private:

		// Transforms

		Mat4 GoalTransform { 1.f };
		Mat4 FrameTransform { 1.f };
		Mat4 LastTransform { 1.f };

		// Game

		Game* GameModel;
		Object* Parent = nullptr;
		
		std::string ID;

		// Children

		std::vector<Object*> Children = {};
		void RemoveChild(Object* instance);

		friend class Game;

	};

}