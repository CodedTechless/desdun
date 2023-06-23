#pragma once

#include <desdun_engine/include/imgui/imgui.h>
#include <desdun_engine/include/imgui/imgui_impl_opengl3.h>
#include <desdun_engine/include/imgui/imgui_impl_glfw.h>
#include <desdun_engine/include/ddlib/core.hpp>

#include <desdun_engine/src/app/app.h>
#include <desdun_engine/src/graphics/render/renderer.h>

#include "imgui_layer.h"

namespace Desdun
{

	ImGuiLayer::ImGuiLayer(const String& configName)
		: Layer("ImGuiLayer")
	{
		configPath = Resource::transformPath(configName);
	}

	void ImGuiLayer::onAwake()
	{
		// Set up ImGui for debug UI and shit like that
		IMGUI_CHECKVERSION();											// check the currently running version
		ImGui::CreateContext();											// create the ImGui context

		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = NULL;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_DpiEnableScaleFonts;

		ImGui::LoadIniSettingsFromDisk(configPath.c_str());

		ImGui::StyleColorsDark();										// sets the window colour style to dark mode

		ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);	// bind it to the currently active GLFW window
		ImGui_ImplOpenGL3_Init((char*)glGetString(330));				// initialises it in OpenGL mode
	}

	void ImGuiLayer::onDestroyed()
	{
		ImGui::SaveIniSettingsToDisk(configPath.c_str());

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::onFrameUpdate(float delta)
	{
		frames++;
		time += delta;

		if (time > 1.f)
		{
			time -= 1.f;

			lastFrameCount = frames;
			frames = 0.f;
		}

		if (ImGui::Begin("Debugger"))
		{
			auto* app = Application::get();	

			if (ImGui::CollapsingHeader("Peformance"))
			{
				if (ImGui::BeginTable("performanceTable", 2))
				{
					ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
					ImGui::TableSetupColumn("Stat", ImGuiTableColumnFlags_WidthFixed);
					ImGui::TableHeadersRow();

					ImGui::TableNextColumn();
					ImGui::Text("FPS");
					ImGui::TableNextColumn();
					ImGui::Text(std::to_string((uint)lastFrameCount).c_str());

					ImGui::TableNextColumn();
					ImGui::Text("Frame time");
					ImGui::TableNextColumn();
					ImGui::Text((std::to_string(delta * 1000.f) + "ms").c_str());

					ImGui::EndTable();
				}
			};

			if (ImGui::CollapsingHeader("Graphics"))
			{
				if (ImGui::BeginTable("graphicsTable", 2))
				{
					ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
					ImGui::TableSetupColumn("Stat", ImGuiTableColumnFlags_WidthFixed);
					ImGui::TableHeadersRow();

					auto frameData = app->getRenderer()->performance();

					ImGui::TableNextColumn();
					ImGui::Text("Draw calls");
					ImGui::TableNextColumn();
					ImGui::Text(std::to_string(frameData.drawCalls).c_str());

					ImGui::TableNextColumn();
					ImGui::Text("Vertex count");
					ImGui::TableNextColumn();
					ImGui::Text(std::to_string(frameData.vertexCount).c_str());

					auto* window = Application::get()->getPrimaryWindow();
					auto size = window->getSize();

					ImGui::TableNextColumn();
					ImGui::Text("Window resolution");
					ImGui::TableNextColumn();
					ImGui::Text(std::string(std::to_string((uint)size.x) + "x" + std::to_string((uint)size.y)).c_str());

					ImGui::EndTable();
				}
			};

			if (ImGui::CollapsingHeader("Layer Stack"))
			{
				for (auto* layer : app->gameLayers)
				{
					ImGui::Text(layer->name().c_str());
				}
			}
			
			if (ImGui::CollapsingHeader("Resources"))
			{
				for (auto& [typeIndex, resourceCollection] : Resource::getResources())
				{
					if (ImGui::TreeNodeEx(typeIndex.name(), ImGuiTreeNodeFlags_OpenOnArrow))
					{
						for (auto& [path, _] : resourceCollection)
						{
							ImGui::Text(path.c_str());
						}

						ImGui::TreePop();
					}
				}
			};

			ImGui::End();
		}
	}

	void ImGuiLayer::onInputEvent(Input::Event& inputEvent)
	{
		if (!absorbInputs)
		{
			return;
		}

		auto& io = ImGui::GetIO();

		if ((inputEvent.action.type == Input::Type::Mouse ||
			inputEvent.action.type == Input::Type::MouseScrolling) &&
			io.WantCaptureMouse == true)
		{
			inputEvent.absorbed = true;
		}
		else if (inputEvent.action.type == Input::Type::Keyboard &&
			io.WantCaptureKeyboard == true)
		{
			inputEvent.absorbed = true;
		}
	}

	void ImGuiLayer::begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::end()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

}