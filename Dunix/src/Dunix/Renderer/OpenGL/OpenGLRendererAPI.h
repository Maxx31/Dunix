#pragma once

#include "Dunix/Renderer/RendererApi.h"

namespace Dunix {

	class OpenGLRendererAPI : RendererAPI
	{
		virtual void Init() override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<class VertexArray>& vertexArray) override;
	};
}

