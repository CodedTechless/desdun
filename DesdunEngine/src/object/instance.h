#pragma once

#include <app/app.h>
#include <app/input.h>
#include <app/runtime.h>

#include <core_lib.hpp>

namespace Desdun
{

	class Scene;

	class Instance : public RuntimeObject
	{
	public:

		std::string name = "Instance";

	private:

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

		std::string id;
		HierarchyMember hierarchyTree = {};

		Scene* activeScene = nullptr;
		bool active = false;

	public:
		RUNTIME_CLASS_DEF(Instance);

		Instance() = default;
		~Instance();

		virtual void onAwake() {};
		virtual void onDestroyed() {};

		virtual void onGameStep(const float_t Delta) {};
		virtual void onFrameUpdate(const float_t Delta) {};

		virtual void onInputEvent(Input::Event& input) { };
		virtual void onWindowEvent(const Window::Event& window) {};

		// Object operations

		void saveToFile(const std::string& path) const;
		void setParent(Instance* object);

		Instance* findChild(const std::string& name) const;

		template<typename T>
		T* findAncestor() const
		{
			Instance* next = getParent();

			while (next != nullptr && next->isA<T>() == false)
			{
				next = next->getParent();
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
		bool isA() const
		{
			return Runtime::Get(getClassIndex())->isA<T>();
		}

		// Getters

		std::string getInstanceId() const { return id; };
		Scene* getScene() const { return activeScene; };

		const std::vector<Instance*>& getChildren() const { return hierarchyTree.m_Container; };
		Instance* getParent() const { return hierarchyTree.m_Parent; };

		Instance* operator[](uint idx) const { return hierarchyTree.m_Container[idx]; };
		Instance* operator[](const std::string& name) const { return findChild(name); };

	protected:

		void serialise(JSONObject& object) const override;
		void deserialise(const JSONObject& object) override;

	private:

		void removeChild(Instance* instance);

		friend class Scene;
		friend class Model;
	};
}
