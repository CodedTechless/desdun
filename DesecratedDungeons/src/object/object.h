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

#include <resource/serial/byte_file.h>

#include <libraries.hpp>

#define CLASS_DEF(v) std::string GetClassName() const { return v; };

namespace Desdun
{

	class Scene;

	class Object
	{
	public:

		// Properties

		std::string Name = "Object";

		Vector2 Position = { 0.f, 0.f };
		Vector2 Scale = { 1.f, 1.f };
		float Rotation = 0.f;

		float ZIndex = 0.f;

		bool Visible = true;
		bool Interpolate = true;

		Object() = default;
		Object(Object&&) = delete;
		Object(const Object& object);

		~Object();

		// Virtuals

		virtual CLASS_DEF("Object");

		virtual void OnAwake() {};
		virtual void OnDestroyed() {};

		virtual void OnGameStep(const float Delta) {};
		virtual void OnFrameUpdate(const float Delta) {};

		virtual Input::Filter OnInputEvent(InputEvent input, bool processed) { return Input::Filter::Ignore; };
		virtual void OnWindowEvent(WindowEvent window) {};

		// Object operations

		void SetParent(Object* object);
		Object* FindChild(const std::string& name);

		void SaveToFile(const std::string& path);

		// Getters

		std::string GetObjectID() const { return ID; };
		Scene* GetScene() const { return m_ActiveScene; };

		const std::vector<Object*>& GetChildren() const { return Children; };
		Object* GetParent() const { return Parent; };
		
		Object* operator[](uint idx) { return Children[idx]; };
		Object* operator[](const std::string& name) { return FindChild(name); };

		// Transforms

		Mat4 GetInterpTransform() const;
		Mat4 GetTransform() const;
		Mat4 GetGlobalTransform() const;
		
		// Static

		static Object* CreateObjectByName(const std::string& name);

	protected:

		virtual void Serialise(ByteFile& stream);
		virtual void Deserialise(ByteFile& stream);

	private:

		bool Active = false;


		// Transforms

		Vector2 LastPosition = Position;
		Vector2 LastScale = Scale;
		float LastRotation = Rotation;

		// Game

		Scene* m_ActiveScene = nullptr;
		Object* Parent = nullptr;
		std::vector<Object*> Children = {};
		
		std::string ID;

		// Children

		void RemoveChild(Object* instance);

		friend class Scene;
		friend class Model;

	};

}