#pragma once

#include <libraries.hpp>

#include <app/input/input.h>
#include <app/input/event.h>

#include <core/resource/external/image.h>

/*
	Base class of all Instances.
*/

namespace Desdun
{

	class Game;

	class Instance
	{
	public:

		Instance(Game* game, const std::string& id);
		~Instance();
		
		std::string Name = "Instance";

		// Virtuals

		virtual void OnAwake() {};
		virtual void OnDestroyed() {};

		virtual void OnGameStep(const float Delta) {};
		virtual void OnFrameUpdate(const float Delta) {};

		virtual Input::Filter OnInputEvent(InputEvent input, bool processed) { return Input::Filter::Ignore; };
		virtual void OnWindowEvent(WindowEvent window) {};

		// Drawing

		void DrawImage(ptr<Image> image);

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

		Game* GameModel;
		Instance* Parent = nullptr;
		
		std::string ID;

		std::vector<Instance*> Children = {};
		void RemoveChild(Instance* instance);

		friend class Game;

	};

}