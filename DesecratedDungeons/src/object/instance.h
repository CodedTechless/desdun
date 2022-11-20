#pragma once

#include <app/app.h>
#include <app/input/input.h>
#include <app/input/event.h>

#include <resource/serial/byte_file.h>

#include <app/runtime_info.h>

#include <libraries.hpp>

#define RUNTIME_CLASS_DEF(x) \
	std::type_index GetClassIndex() const override { return typeid(x); } \

namespace Desdun
{

	class Scene;

	class Instance
	{
	public:
		Instance() = default;
		~Instance();

		virtual std::type_index GetClassIndex() const { return typeid(Instance); };

		std::string Name = "Instance";

		virtual void OnAwake() {};
		virtual void OnDestroyed() {};

		virtual void OnGameStep(const float Delta) {};
		virtual void OnFrameUpdate(const float Delta) {};

		virtual Input::Filter OnInputEvent(InputEvent input, bool processed) { return Input::Filter::Ignore; };
		virtual void OnWindowEvent(WindowEvent window) {};

		// Object operations

		void SetParent(Instance* object);

		Instance* FindChild(const std::string& name) const;

		template<typename T>
		T* FindAncestor() const
		{
			Instance* next = GetParent();

			while (next != nullptr && next->IsA<T>() == false)
			{
				next = next->GetParent();
			}

			if (next == nullptr)
			{
				return nullptr;
			}
			else
			{
				return (T*)next;
			}
		}

		void SaveToFile(const std::string& path) const;

		template<typename T>
		bool IsA() const
		{
			return Runtime::Get(GetClassIndex())->IsA<T>();
		}

		// Subclass

		struct HierarchyMember
		{
			HierarchyMember() = default;
			HierarchyMember(const HierarchyMember&) {};

			HierarchyMember& operator=(const HierarchyMember&)
			{
				return *this;
			};

		private:

			Instance* m_Parent = nullptr;
			std::vector<Instance*> m_Container = {};

			friend class Instance;

		};

		// Getters

		std::string GetInstanceID() const { return ID; };
		Scene* GetScene() const { return m_ActiveScene; };

		const std::vector<Instance*>& GetChildren() const { return m_Relation.m_Container; };
		Instance* GetParent() const { return m_Relation.m_Parent; };

		Instance* operator[](uint idx) const { return m_Relation.m_Container[idx]; };
		Instance* operator[](const std::string& name) const { return FindChild(name); };

	protected:

		virtual void Serialise(ByteFile& stream) const;
		virtual void Deserialise(ByteFile& stream);

	private:

		// Game

		bool Active = false;

		std::string ID;
		Scene* m_ActiveScene = nullptr;

		HierarchyMember m_Relation = {};

		// Children

		void RemoveChild(Instance* instance);

		friend class Scene;
		friend class Model;

	};
}
