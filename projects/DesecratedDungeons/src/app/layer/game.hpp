#pragma once

#include <src/desdun_engine.hpp>

namespace Desdun
{

	class Game : public Layer
	{
	public:

		Scene* gameScene = nullptr;

		Game() = default;
		Game(const std::string& name)
			: Layer(name) {};

		void onAwake() override;

		void onFrameUpdate(const float delta) override;
		void onGameStep(const float delta) override;

		void onInputEvent(Input::Event& inputObject) override;
		void onWindowEvent(const Window::Event& windowEvent) override;

	private:

		SceneExplorer* explorer = nullptr;

	};

}