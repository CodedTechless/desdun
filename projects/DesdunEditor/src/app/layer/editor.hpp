

#include <app/panel/scene_explorer.hpp>

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

	private:

		Scene* editorScene = nullptr;
		SceneExplorer* explorer = nullptr;

		bool setup = false;

	};

}