
#include <app/editor_app.hpp>
#include <app/layer/editor.hpp>

namespace DesdunEditor
{

	void DesdunEditorApp::init()
	{
		Application::init();

		Layer* newLayer = new EditorLayer();
		gameLayers.PushLayer(newLayer);

		start();
	};

}