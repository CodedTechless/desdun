

#include <app/panel/scene_explorer.hpp>

#include <desdun_engine.hpp>

using namespace Desdun;

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

	private:

		Scene* editorScene = nullptr;
		SceneExplorer* explorer = nullptr;

	};

}