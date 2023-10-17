

#include <app/panel/scene_explorer.hpp>
#include <app/panel/scene_viewport.hpp>

#include <imgui/imgui.h>

#include <desdun_engine.hpp>

using namespace DesdunCore;

namespace DesdunEditor
{

	class EditorLayer : public Layer
	{
	public:
		EditorLayer() = default;
		EditorLayer(const std::string& name)
			: Layer(name) {};

		void onAwake() override;

		void onFrameUpdate(const float delta) override;
		void onGameStep(const float delta) override;

		void onInputEvent(Input::Event& event) override;
		void onWindowEvent(const Window::Event& event) override;

		void buildMenuBar();
		void buildDockspace(ImGuiDockNodeFlags flags = 0);

	private:
		Scene* editorScene = nullptr;

		bool sceneFocused = false;

	};

}