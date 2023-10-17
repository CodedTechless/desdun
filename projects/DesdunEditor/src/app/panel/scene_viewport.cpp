
#include "scene_viewport.hpp"

#include <desdun_engine.hpp>
#include <imgui/imgui.h>

namespace DesdunEditor
{


	bool SceneViewport::render(Scene* scene, const float delta)
	{
        bool isFocused = false;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("Viewport");
        ImGui::PopStyleVar();
        {
            isFocused = ImGui::IsWindowFocused() && ImGui::IsWindowHovered();

            ImVec2 region = ImGui::GetContentRegionAvail();
            Vector2 viewportSize = { region.x, region.y };

            auto& camViewport = scene->currentCamera->viewport;
            camViewport->Resize(viewportSize);
            scene->onFrameUpdate(delta);

            //ImGui::PushID("ViewportDropZone");

            uint32_t rid = camViewport->GetColourAttachmentRendererID();

            //ImVec2 CursorScreenPos = ImGui::GetCursorScreenPos();
            //c_Camera.SetViewportPosition({ CursorScreenPos.x, CursorScreenPos.y });
            ImGui::Image((ImTextureID)rid, ImVec2{ (float)viewportSize.x, (float)viewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
        }
        ImGui::End();

        return isFocused;
	}

}