#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Buffer.h"

namespace Dunix {
	
	class RendererAPI
	{
	public:
		virtual void Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(class VertexArray* vertexArray) = 0;

		static RendererAPI* Create();
	};

}