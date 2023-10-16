
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include <objects/object.hpp>

#include "scene_explorer.hpp"

namespace DesdunCore
{

	SceneExplorer::SceneExplorer()
	{
	}

	void SceneExplorer::setContextScene(Scene* inst)
	{
		scene = inst;
	}

	void SceneExplorer::onImGuiRender()
	{
		ImGui::Begin("Scene Explorer");
		
		if (scene != nullptr)
		{
			renderInstance(scene->getRoot());
		}

		ImGui::End();
	}

	void SceneExplorer::renderInstance(Object* instance)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

		if (instance->getChildren().size() == 0)
		{
			flags |= ImGuiTreeNodeFlags_Leaf;
		}

		bool open = ImGui::TreeNodeEx(instance->getInstanceId().c_str(), flags, instance->name.c_str());

		if (open)
		{
			for (auto* child : instance->getChildren())
			{
				renderInstance(child);
			}

			ImGui::TreePop();
		}
	}

}