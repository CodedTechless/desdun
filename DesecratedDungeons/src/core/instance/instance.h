#pragma once

#include <libraries.hpp>

namespace Desdun
{

	class Instance
	{
	public:
		Instance() = default;
		
		std::string Name = "Instance";

		virtual void OnAwake() {};
		virtual void OnDestroyed() {};

		virtual void OnFrameUpdate(const float Delta) {};
		virtual void OnGameStep(const float Delta) {};

		virtual Input::Filter OnInputEvent(InputEvent input, bool processed) { return Input::Filter::Ignore; };
		virtual void OnWindowEvent(WindowEvent window) {};

	private:
		uint ID = 0;

		ptr<Instance> Parent = nullptr;
		std::vector<ptr<Instance>> Children = {};

	};

}