#pragma once

#include <scene/scene.h>

#include <app/layers/layer.h>
#include <app/input/input.h>
#include <app/input/event.h>

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

		Scene* GameScene = nullptr;

	};

}