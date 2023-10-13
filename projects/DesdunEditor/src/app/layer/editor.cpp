

#include <imgui/imgui.h>

#include "editor.hpp"

namespace DesdunEditor
{

    void EditorLayer::onAwake()
    {
        editorScene = new Scene();

        Application::get()->getPrimaryWindow()->setVsyncEnabled(true);

        explorer = new SceneExplorer();
        explorer->setContextScene(editorScene);
    }

	void EditorLayer::onFrameUpdate(const float delta)
	{
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

            dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;

            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;
        }

        ImGui::Begin("Editor", nullptr, window_flags);
        ImGui::PopStyleVar(3);
        {
            ImGuiID dockspace_id = ImGui::GetID("editor_dockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Edit"))
                {

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

        }
        ImGui::End();

        explorer->onImGuiRender();
	}

}