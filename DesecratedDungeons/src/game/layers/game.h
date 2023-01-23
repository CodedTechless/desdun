#pragma once

#include <scene/scene.h>

#include <app/layers/layer.h>
#include <app/input.h>

namespace Desdun
{

	class Game : public Layer
	{
	public:

		Game() = default;
		Game(const std::string& name)
			: Layer(name) {};

		void onAwake() override;

		void onFrameUpdate(const float delta) override;
		void onGameStep(const float delta) override;

		void onInputEvent(Input::Event& inputObject) override;
		void onWindowEvent(const Window::Event& windowEvent) override;

		Scene* gameScene = nullptr;

	};

}