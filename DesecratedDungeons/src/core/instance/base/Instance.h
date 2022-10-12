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
	public: // Class definitions

		Instance(Game* game, const std::string& id);
		~Instance();
		
		std::string Name = "Instance";

		// Virtuals

		virtual void OnAwake() {};
		virtual void OnDestroyed() {};

		virtual void OnFrameUpdate(const float Delta) {};
		virtual void OnGameStep(const float Delta) {};

		virtual Input::Filter OnInputEvent(InputEvent input, bool processed) { return Input::Filter::Ignore; };
		virtual void OnWindowEvent(WindowEvent window) {};

		// Instance operations

		void SetParent(Instance* instance);
		Instance* FindChild(const std::string& name);

		// Getters

		std::string GetInstanceID() const { return ID; };
		Game* GetGameModel() const { return GameModel; };

		const std::vector<Instance*>& GetChildren() const { return Children; };
		Instance* GetParent() const { return Parent; };
		
		Instance* operator[](uint idx)
		{
			return Children[idx];
		}

	private:

		Instance* Parent = nullptr;
		std::vector<Instance*> Children = {};

		std::string ID;
		Game* GameModel;

		void RemoveChild(Instance* instance);

	};

}