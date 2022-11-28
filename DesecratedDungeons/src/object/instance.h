#pragma once

#include <app/app.h>
#include <app/input/input.h>
#include <app/input/event.h>
#include <app/runtime_info.h>

//#include <resource/serial/byte_stream.h>
#include <resource/serial/json_stream.h>

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

		string Name = L"Instance";

		virtual void OnAwake() {};
		virtual void OnDestroyed() {};

		virtual void OnGameStep(const double_t Delta) {};
		virtual void OnFrameUpdate(const double_t Delta) {};

		virtual Input::Filter OnInputEvent(InputEvent input, bool processed) { return Input::Filter::Ignore; };
		virtual void OnWindowEvent(WindowEvent window) {};

		virtual std::type_index GetClassIndex() const { return typeid(Instance); };

		// Object operations

		void SaveToFile(const string& path) const;
		void SetParent(Instance* object);

		Instance* FindChild(const string& name) const;

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

		template<typename T>
		bool IsA() const
		{
			return Runtime::Get(GetClassIndex())->IsA<T>();
		}

		// Getters

		string GetInstanceID() const { return m_ID; };
		Scene* GetScene() const { return m_ActiveScene; };

		const std::vector<Instance*>& GetChildren() const { return m_Relation.m_Container; };
		Instance* GetParent() const { return m_Relation.m_Parent; };

		Instance* operator[](uint idx) const { return m_Relation.m_Container[idx]; };
		Instance* operator[](const string& name) const { return FindChild(name); };

	protected:

#if 0
		virtual void Serialise(ByteObject& object) const;
		virtual void Deserialise(ByteObject& object);
#endif

		virtual void Serialise(JSONObject& object) const;
		virtual void Deserialise(const JSONObject& object);

	private:

		void RemoveChild(Instance* instance);

		// Game

		string m_ID;
		HierarchyMember m_Relation = {};
		
		Scene* m_ActiveScene = nullptr;
		bool m_Active = false;

		friend class Scene;
		friend class Model;
		friend class JSONStream;
	};
}
