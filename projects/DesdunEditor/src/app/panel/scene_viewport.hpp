#pragma once

#include <runtime/scene/scene.hpp>

using namespace DesdunCore;

namespace DesdunEditor
{

	class SceneViewport
	{
	public:
		static bool render(Scene* scene, const float delta);
	};

}