#pragma once

#include "RenderCommand.h"
#include "Buffer.h"
#include "Camera.h"
#include "RendererAPI.h"

namespace Dunix {
	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void Submit(VertexArray* vertexArray);
	};
}