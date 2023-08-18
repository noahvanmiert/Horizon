/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#include "hrpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <Glad/glad.h>

namespace Horizon {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		HR_CORE_ASSERT(windowHandle, "Window handle is null!");
	}


	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HR_CORE_ASSERT(status, "Failed to initialize Glad!");

		/* print some info about the renderer */
		HR_CORE_INFO("OpenGL Info");
		HR_CORE_INFO("    Vendor   -> {0}", (const char*) glGetString(GL_VENDOR));
		HR_CORE_INFO("    Renderer -> {0}", (const char*) glGetString(GL_RENDERER));
		HR_CORE_INFO("    Version  -> {0}", (const char*) glGetString(GL_VERSION));
	}


	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}