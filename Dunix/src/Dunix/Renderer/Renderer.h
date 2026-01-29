#pragma once

#include "RenderCommand.h"
#include "Buffer.h"

#include "RendererAPI.h"

namespace Dunix {
	class Renderer
	{
	private:
		static void BeginScene();
		static void EndScene();

		static void Submit(VertexArray* vertexArray);
	};
}