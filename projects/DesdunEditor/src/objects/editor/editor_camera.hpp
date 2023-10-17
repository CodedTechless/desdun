#pragma once

#include <desdun_engine.hpp>

using namespace DesdunCore;

namespace DesdunEditor
{


	class EditorCamera2D : public Camera2D
	{
	public:

		void onAwake() override;

		void onInputEvent(Input::Event& event) override;

	};

}