#pragma once

#include <app/app.hpp>
#include <app/window/input.hpp>
#include <runtime/runtime.hpp>

#include <corelib/core.hpp>

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

	class Object : public Serialisable
	{
	public:
		serialisable(Object);

		String name = "Object";

		Object() = default;
		~Object();

		virtual void onAwake() {};
		virtual void onDestroyed() {};

		virtual void onGameStep(const float_t Delta) {};
		virtual void onFrameUpdate(const float_t Delta) {};

		virtual void onInputEvent(Input::Event& input) {};
		virtual void onWindowEvent(const Window::Event& window) {};

		// Object operations

		void saveToFile(const std::string& path) const;
		void setParent(Object* object);

		Object* findChild(const std::string& name) const;

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
			Object* next = getParent();

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

		const List<Object*>& getChildren() const { return hierarchyTree.m_Container; };
		Object* getParent() const { return hierarchyTree.m_Parent; };

		Object* operator[](uint idx) const { return hierarchyTree.m_Container[idx]; };
		Object* operator[](const std::string& name) const { return findChild(name); };

		Object* clone() const;

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
			Object* m_Parent = nullptr;
			std::vector<Object*> m_Container = {};

			friend class Object;
		};

		HierarchyMember hierarchyTree = {};

		void removeChild(Object* instance);

		friend class Scene;
		friend class Model;
	};
}
