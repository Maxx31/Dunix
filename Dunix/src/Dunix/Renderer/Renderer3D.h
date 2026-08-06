#pragma once

#include "RenderCommand.h"
#include "RendererAPI.h"

#include "Buffer.h"

#include <glm/glm.hpp>

namespace Dunix {
	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const class Camera& camera);
		static void EndScene();

		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color, int entityID = -1);
		static void DrawCube(const glm::vec3& position, const glm::vec3& size, const class Texture3D* texture, int entityID = -1);
		static void DrawMesh(const class Mesh& mesh, const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f), int entityID = -1);
		static void DrawModel(const class Model& model, const glm::mat4& transform, const glm::vec4& color = glm::vec4(1.0f), int entityID = -1);
	};
}
