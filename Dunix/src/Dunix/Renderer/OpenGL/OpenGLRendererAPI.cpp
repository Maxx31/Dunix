#include "dxpch.h"
#include "OpenGLRendererAPI.h"
#include <gl/GL.h>

namespace Dunix {

	void OpenGLRendererAPI::Init()
	{
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
	}

	void OpenGLRendererAPI::Clear()
	{
		glClearColor(0.137, 0.137, 0.137, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<class VertexArray>& vertexArray)
	{
	}
}
