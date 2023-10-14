#pragma once

#include <runtime/scene/scene.hpp>

namespace DesdunCore
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

		void renderInstance(Object* instance);

	};


}