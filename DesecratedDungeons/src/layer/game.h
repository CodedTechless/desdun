#pragma once

#include <scene/scene.h>

#include <app/panel/scene_explorer.h>
#include <app/layer/layer.h>
#include <app/input.h>

#include <src/world/item.hpp>

namespace Desdun
{

	class Game : public Layer
	{
	public:

		Scene* gameScene = nullptr;

		Map<String, Provider<Item>> items = {};

		Game() = default;
		Game(const std::string& name)
			: Layer(name) {};

		void onAwake() override;

		void onFrameUpdate(const float delta) override;
		void onGameStep(const float delta) override;

		void onInputEvent(Input::Event& inputObject) override;
		void onWindowEvent(const Window::Event& windowEvent) override;

	private:

		SceneExplorer explorer;

	};

}