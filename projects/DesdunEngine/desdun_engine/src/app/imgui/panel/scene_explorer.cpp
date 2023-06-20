
#include <desdun_engine/include/imgui/imgui.h>
#include <desdun_engine/include/imgui/imgui_internal.h>

#include <desdun_engine/src/instance/instance.hpp>

#include "scene_explorer.h"

namespace Desdun
{

	void SceneExplorer::setContextScene(Scene* inst)
	{
		scene = inst;
	}

	void SceneExplorer::onImGuiRender()
	{
		ImGuiID id = ImGui::GetID("giraffeDock");
		ImGui::DockSpace(id, {})

			
		if (ImGui::Begin("giraffe™️"))
		{
			ImGui::DockBuilderDockWindow()
			if (ImGui::Begin("Scene Explorer"));

			if (scene != nullptr)
				renderInstance(scene->getRoot());

			ImGui::End();

			ImGui::End();
		}

	}

	void SceneExplorer::renderInstance(Instance* instance)
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