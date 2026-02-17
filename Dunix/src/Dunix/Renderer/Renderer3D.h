#pragma once

#include "RenderCommand.h"
#include "RendererAPI.h"

#include "Buffer.h"

namespace Dunix {
	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene();
		static void EndScene();

		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
	};
}