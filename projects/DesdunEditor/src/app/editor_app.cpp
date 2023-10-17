
#include <app/editor_app.hpp>
#include <app/layer/editor.hpp>
#include <objects/editor/editor_camera.hpp>

namespace DesdunEditor
{

	void DesdunEditorApp::init()
	{
		Application::init();

		Runtime::add<EditorCamera2D>({ "EditorCamera2D", Runtime::get<Camera2D>() });

		Layer* newLayer = new EditorLayer();
		gameLayers.PushLayer(newLayer);

		start();
	};

}