#pragma once

#include <src/app/app.h>
#include <src/app/window/input.h>
#include <src/app/runtime/runtime.h>

#include <include/desdun_core.hpp>

namespace Desdun
{

	// TODO: remove need for instance to be in a scene for cloning

	class NoActiveSceneException : public virtual Exception
	{
	public:
		NoActiveSceneException(const String& id)
			: Exception("Cannot clone instance {} as it doesn't exist in any active scene.") {};

	};

	class Scene;

	class Instance : public Serialisable
	{
	public:
		serialisable(Instance);

		std::string name = "Instance";

		Instance() = default;
		~Instance();

		virtual void onAwake() {};
		virtual void onDestroyed() {};

		virtual void onGameStep(const float_t Delta) {};
		virtual void onFrameUpdate(const float_t Delta) {};

		virtual void onInputEvent(Input::Event& input) {};
		virtual void onWindowEvent(const Window::Event& window) {};

		// Object operations

		void saveToFile(const std::string& path) const;
		void setParent(Instance* object);

		Instance* findChild(const std::string& name) const;

		template<typename T>
		T* findChildOfType() const
		{
			for (auto* child : getChildren())
			{
				if (child->isA<T>())
					return child;
			}

			return nullptr;
		}

		template<typename T>
		T* findAncestorOfType() const
		{
			Instance* next = getParent();

			while (next and next->isA<T>() == false)
			{
				next = next->getParent();
			}

			if (next == nullptr)
				return nullptr;
			else
				return (T*)next;
		}

		template<typename T>
		bool isA() const
		{
			return Runtime::get(getClassIndex())->isA<T>();
		}

		// Getters

		std::string getInstanceId() const { return id; };
		Scene* getScene() const { return activeScene; };

		const List<Instance*>& getChildren() const { return hierarchyTree.m_Container; };
		Instance* getParent() const { return hierarchyTree.m_Parent; };

		Instance* operator[](uint idx) const { return hierarchyTree.m_Container[idx]; };
		Instance* operator[](const std::string& name) const { return findChild(name); };

		Instance* clone() const;

	protected:

		virtual void markDirty();

		void serialise(JSONObject& object) const override;
		void deserialise(const JSONObject& object) override;

	private:

		std::string id;

		Scene* activeScene = nullptr;
		bool active = false;

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

		HierarchyMember hierarchyTree = {};

		void removeChild(Instance* instance);

		friend class Scene;
		friend class Model;
	};
}
