
#include <app/editor_app.hpp>
#include <app/layer/editor.hpp>
#include <objects/editor/editor_camera.hpp>

namespace DesdunEditor
{

	void DesdunEditorApp::init()
	{
		Application::init();

		auto& state = getScriptEngine()->getState();

		dd_define_type_inheritence(EditorCamera2D, { Runtime::get<Camera2D>() },
			sol::no_constructor,
			sol::base_classes, sol::bases<Camera2D>()
		);

		Layer* newLayer = new EditorLayer();
		gameLayers.PushLayer(newLayer);

		start();
	};

}