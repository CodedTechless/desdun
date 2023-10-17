

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#include "editor.hpp"

namespace DesdunEditor
{

    void EditorLayer::onAwake()
    {
        editorScene = new Scene();

        auto* app = Application::get();
        app->getPrimaryWindow()->setVsyncEnabled(true);
        app->getImGuiLayer()->absorbInputs = false;

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

        const ImGuiViewport* imviewport = ImGui::GetMainViewport();
        {
            ImGui::SetNextWindowPos(imviewport->WorkPos);
            ImGui::SetNextWindowSize(imviewport->WorkSize);
            ImGui::SetNextWindowViewport(imviewport->ID);
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
        
        buildMenuBar();
        buildDockspace(dockspace_flags);

        sceneFocused = SceneViewport::render(editorScene, delta);
        SceneExplorer::render(editorScene);

        ImGui::Begin("Inspector");
        ImGui::End();

        ImGui::Begin("Output");
        ImGui::End();

        Application::get()->showDebug();

        ImGui::End();
	}


    void EditorLayer::onGameStep(const float Delta)
    {
        editorScene->onGameStep(Delta);
    }

    void EditorLayer::onInputEvent(Input::Event& event)
    {
        if (sceneFocused)
        {
            editorScene->onInputEvent(event);
        }
    }

    void EditorLayer::onWindowEvent(const Window::Event& event)
    {
        editorScene->onWindowEvent(event);
    }

    void EditorLayer::buildMenuBar()
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::MenuItem("Save", "Ctrl+S");
                ImGui::MenuItem("Load", "Ctrl+L");


                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }
    }

    void EditorLayer::buildDockspace(ImGuiDockNodeFlags flags)
    {
        const ImGuiViewport* imviewport = ImGui::GetMainViewport();

        ImGuiID id = ImGui::GetID("editor_dockspace");
        ImGui::DockSpace(id, ImVec2(0.0f, 0.0f), flags);

        static bool setup = false;
        if (not setup)
        {

            ImGui::DockBuilderRemoveNode(id);
            ImGui::DockBuilderAddNode(id, flags | ImGuiDockNodeFlags_DockSpace);

            ImGui::DockBuilderSetNodeSize(id, imviewport->Size);

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
}