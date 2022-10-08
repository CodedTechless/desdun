
#include <core/debug/debug.h>

#include <GL/glew.h>
#include <glfw3.h>

#include <libraries.hpp>

#include "interface.h"


namespace Desdun
{
	RenderInterface::RenderCore m_RenderCore = {};

	void RenderInterface::Start()
	{
		// Debug Output

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		
		glDebugMessageCallback(Debug::OpenGLMessage, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

		// Modes

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RenderInterface::Stop()
	{
		glfwTerminate();
	}

	void RenderInterface::BeginScene(const RenderCamera& Camera)
	{
		
	}

	void RenderInterface::EndScene()
	{

	}

}