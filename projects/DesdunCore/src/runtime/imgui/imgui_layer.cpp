#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <corelib/core.hpp>

#include <app/app.hpp>
#include <graphics/render/renderer.hpp>

#include "imgui_layer.hpp"

namespace DesdunCore
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
		ImGui_ImplOpenGL3_Init();				// initialises it in OpenGL mode
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