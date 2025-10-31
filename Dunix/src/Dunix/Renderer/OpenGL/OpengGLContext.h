#pragma once

#include "../GraphicsContext.h"
#include <GLFW/glfw3.h>

 namespace Dunix
{
	class OpengGLContext : public GraphicsContext
	{
	public:
		OpengGLContext(GLFWwindow* w);

		virtual ~OpengGLContext() override;
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;
	};
}

