#pragma once

#include <libraries.hpp>

#include <app/input/input.h>
#include <app/input/event.h>

/*
	Base class of all Instances.
*/

namespace Desdun
{

	class Game;

	class Instance
	{
	public:
		Instance() = default;
		Instance(Game* game, const std::string& id)
			: GameModel(game), ID(id) {};

		virtual ~Instance() = default;
		
		std::string Name = "Instance";

		virtual void OnAwake() {};
		virtual void OnDestroyed() {};

		virtual void OnFrameUpdate(const float Delta) {};
		virtual void OnGameStep(const float Delta) {};

		virtual Input::Filter OnInputEvent(InputEvent input, bool processed) { return Input::Filter::Ignore; };
		virtual void OnWindowEvent(WindowEvent window) {};

		void SetParent(ptr<Instance> instance) 
		{
			if (Parent) Parent->RemoveChild(ID);

			Parent = instance;

			Parent->Children.push_back()
		};

		ptr<Instance> FindChild(const std::string& name)
		{
			for (auto instance : Children)
			{
				if (instance->Name == name)
				{
					return instance;
				}
			}
		}

		std::string GetInstanceID() const { return ID; };
		Game* GetGameModel() const { return GameModel; };

		const std::vector<ptr<Instance>>& GetChildren() const { return Children; };
		ptr<Instance> GetParent() const { return Parent; };
		
		ptr<Instance> operator[](uint idx)
		{
			return Children[idx];
		}

	private:

		void RemoveChild(const std::string& instanceID)
		{
			auto it = std::find(Children.begin(), Children.end(),
				[&](ptr<Instance> child)
				{
					return child->GetInstanceID() == instanceID;
				}
			);

			if (it != Children.end())
			{
				Children.erase(it);
			}
		}

		std::string ID = 0;

		ptr<Instance> Parent = nullptr;
		std::vector<ptr<Instance>> Children = {};

		Game* GameModel = nullptr;

	};

}