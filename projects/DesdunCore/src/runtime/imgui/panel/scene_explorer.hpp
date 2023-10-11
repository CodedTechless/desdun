#pragma once

#include <runtime/scene/scene.hpp>

namespace Desdun
{

	class SceneExplorer
	{
	public:
		SceneExplorer();

		void setContextScene(Scene* scene);

		void onImGuiRender();

	private:

		Scene* scene = nullptr;
		bool setup = false;

		void renderInstance(Instance* instance);

	};


}