#include "dxpch.h"
#include <glad/glad.h>
#include "OpengGLContext.h"

namespace Dunix
{
	OpengGLContext::OpengGLContext(GLFWwindow* w)
		: m_Window(w)
	{

	}

	OpengGLContext::~OpengGLContext()
	{

	}

	void OpengGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int ok = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (ok == 0)
		{
			DX_CORE_ERROR("Failed to initialize GLAD");
		}
	}

	void OpengGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}
