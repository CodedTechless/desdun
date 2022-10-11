#pragma once

#include <core/instance/instance.h>

#include <app/layers/layer.h>
#include <app/input/input.h>
#include <app/input/event.h>

#define MAX_INSTANCES 1024

namespace Desdun
{

	class Game : public Layer
	{
	public:
		Game() = default;
		Game(const std::string& Name)
			: Layer(Name) {};

		void OnAwake();

		void OnFrameUpdate(const float Delta);
		void OnGameStep(const float Delta);

		Input::Filter OnInputEvent(InputEvent InputObject, bool Processed);
		void OnWindowEvent(WindowEvent windowEvent);

		template<typename T>
		ptr<T> Create();

	private:
		std::array<ptr<Instance>, MAX_INSTANCES> Instances = {};

		uint InstanceCount = 0;

		ptr<TextureArray> GoofyAhh = nullptr;
	};

}