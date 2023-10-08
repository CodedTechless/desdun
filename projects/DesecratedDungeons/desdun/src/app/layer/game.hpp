#pragma once

#include <desdun/src/game/item/item.hpp>

#include <desdun_engine/desdun_engine.hpp>
#include <desdun_engine/src/runtime/imgui/panel/scene_explorer.h>

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

		SceneExplorer* explorer = nullptr;

	};

}