#pragma once

#include "RenderCommand.h"
#include "OpenGL/OpenGLBuffer.h"

#include "RendererAPI.h"

namespace Dunix {
	class Renderer
	{
	private:
		static RendererAPI m_RendererAPI;
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
	};
}