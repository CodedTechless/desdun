#pragma once

#include <src/app/scene/scene.h>

namespace Desdun
{

	class SceneExplorer
	{
	public:

		void setContextScene(Scene* scene);

		void onImGuiRender();

	private:

		Scene* scene = nullptr;

		void renderInstance(Instance* instance);

	};


}