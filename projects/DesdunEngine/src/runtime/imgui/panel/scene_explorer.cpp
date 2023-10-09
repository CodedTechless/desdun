
#include <include/imgui/imgui.h>
#include <include/imgui/imgui_internal.h>

#include <src/instance/instance.hpp>

#include "scene_explorer.h"

namespace Desdun
{

	SceneExplorer::SceneExplorer()
	{
#if 0
		ImGuiID id = ImGui::GetID("giraffeDock");
		ImGui::DockSpace(id);

		ImGui::DockBuilderDockWindow("giraffe", id);
		ImGui::DockBuilderDockWindow("sceneExplorer", id);
#endif
	}

	void SceneExplorer::setContextScene(Scene* inst)
	{
		scene = inst;
	}

	void SceneExplorer::onImGuiRender()
	{

#if 0
		if (ImGui::Begin("GiraffeTool"))
		{
			ImGuiID id = ImGui::GetID("GiraffeTool");
			if (!setup)
			{
				ImGuiID docid = ImGui::GetID("GiraffeTool Dockspace");
				ImGui::DockBuilderAddNode(docid);

			}
#endif
		if (ImGui::Begin("Scene Explorer"))
		{
			if (scene != nullptr)
				renderInstance(scene->getRoot());
				
			ImGui::End();
		}
#if 0
			ImGui::End();
		}
#endif
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