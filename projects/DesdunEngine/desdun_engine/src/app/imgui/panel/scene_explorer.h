#pragma once

#include <desdun_engine/src/app/scene/scene.h>

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

		void renderInstance(Instance* instance);

	};


}