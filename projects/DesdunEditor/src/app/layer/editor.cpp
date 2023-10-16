

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "editor.hpp"

namespace DesdunEditor
{

    void EditorLayer::onAwake()
    {
        editorScene = new Scene();

        Application::get()->getPrimaryWindow()->setVsyncEnabled(true);

        explorer = new SceneExplorer();
        explorer->setContextScene(editorScene);

        FrameBufferSpecification fbrSpec;
        fbrSpec.Attachments = { FrameBufferFormat::RGBA8 };
        fbrSpec.Size = { 800.f, 600.f };

        auto* camera = editorScene->create<Camera2D>();
        camera->name = "EditorCamera";
        camera->targetViewportSize = { 800, 600 };
        camera->alpha = 15.f;
        camera->viewport = CreateRef<FrameBuffer>(fbrSpec);
        camera->setParent(editorScene->getRoot());

        editorScene->currentCamera = camera;

        auto* imagetest = editorScene->create<Sprite>();
        imagetest->image = Resource::fetch<Image>("textures:dev/goofy.png");
        imagetest->tiles = { 10.f, 10.f };
        imagetest->setScale({ 1.f, 1.f });
        imagetest->setParent(editorScene->getRoot());
    }

	void EditorLayer::onFrameUpdate(const float delta)
	{
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        {
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

            ImGuiID id = ImGui::GetID("editor_dockspace");
            ImGui::DockSpace(id, ImVec2(0.0f, 0.0f), dockspace_flags);

            if (not setup)
            {

                ImGui::DockBuilderRemoveNode(id);
                ImGui::DockBuilderAddNode(id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);

                ImGui::DockBuilderSetNodeSize(id, viewport->Size);

                ImGuiID center = NULL;

                // left panel
                ImGuiID left = ImGui::DockBuilderSplitNode(id, ImGuiDir_Left, 0.2f, nullptr, &id);
                ImGuiID down = ImGui::DockBuilderSplitNode(id, ImGuiDir_Down, 0.2f, nullptr, &id);

                ImGuiID leftDown = ImGui::DockBuilderSplitNode(left, ImGuiDir_Down, 0.5f, nullptr, &left);

                // center panel
                

                ImGui::DockBuilderDockWindow("Scene Explorer", left);
                ImGui::DockBuilderDockWindow("Inspector", leftDown);
                ImGui::DockBuilderDockWindow("Viewport", id);
                ImGui::DockBuilderDockWindow("Debugger", down);
                ImGui::DockBuilderDockWindow("Output", down);

                ImGui::DockBuilderFinish(id);

                setup = true;
            }
        }

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("Viewport");
        ImGui::PopStyleVar();
        {
            //ViewportFocused = ImGui::IsWindowFocused() && ImGui::IsWindowHovered();
            //ActiveEditorScene->ActiveCameraScript->AcceptingInput = ImGui::IsWindowFocused();

            ImVec2 region = ImGui::GetContentRegionAvail();
            Vector2 viewportSize = { region.x, region.y };

            auto& camViewport = editorScene->currentCamera->viewport;
            camViewport->Resize(viewportSize);
            editorScene->onFrameUpdate(delta);

            //ImGui::PushID("ViewportDropZone");

            uint32_t rid = camViewport->GetColourAttachmentRendererID();

            //ImVec2 CursorScreenPos = ImGui::GetCursorScreenPos();
            //c_Camera.SetViewportPosition({ CursorScreenPos.x, CursorScreenPos.y });
            ImGui::Image((ImTextureID)rid, ImVec2{ (float)viewportSize.x, (float)viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        }
        ImGui::End();

        ImGui::Begin("Inspector");
        ImGui::End();

        ImGui::Begin("Output");
        ImGui::End();


        ImGui::End();

        Application::get()->showDebug();

        explorer->onImGuiRender();
	}

    void EditorLayer::onGameStep(const float Delta)
    {
        editorScene->onGameStep(Delta);
    }

    void EditorLayer::onInputEvent(Input::Event& event)
    {
        editorScene->onInputEvent(event);
    }

    void EditorLayer::onWindowEvent(const Window::Event& event)
    {
        editorScene->onWindowEvent(event);
    }

}