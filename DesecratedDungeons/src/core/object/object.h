#pragma once

/*
	base class of all Objects. every game object inherits from this one!
*/

#include <app/input/input.h>
#include <app/input/event.h>

#include <app/app.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtx/compatibility.hpp>

#include <core/serial/byte_file.h>

#include <libraries.hpp>

namespace Desdun
{

	enum class ObjectType
	{
		Object = 0
	};


	class Scene;

	class Object
	{
	public:

		Object() = default;
		~Object();
		
		std::string Name = "Object";

		// Properties

		Vector2 Position = { 0.f, 0.f };
		Vector2 Scale = { 1.f, 1.f };
		float Rotation = 0.f;

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

		void SetParent(Object* object);
		Object* FindChild(const std::string& name);

		virtual void Serialise(ByteFile& stream);
		virtual void Deserialise(ByteFile& stream);

		// Getters

		std::string GetObjectID() const { return ID; };
		Scene* GetScene() const { return m_ActiveScene; };

		const std::vector<Object*>& GetChildren() const { return Children; };
		Object* GetParent() const { return Parent; };
		
		Object* operator[](uint idx)
		{
			return Children[idx];
		}

		// Transforms

		Mat4 GetInterpTransform() const;
		Mat4 GetTransform() const;
		Mat4 GetGlobalTransform() const;

	private:

		// Transforms

		Vector2 LastPosition = Position;
		Vector2 LastScale = Scale;
		float LastRotation = Rotation;

		// Game

		Scene* m_ActiveScene = nullptr;
		Object* Parent = nullptr;
		
		std::string ID;

		// Children

		std::vector<Object*> Children = {};
		void RemoveChild(Object* instance);

		friend class Scene;

	};

}