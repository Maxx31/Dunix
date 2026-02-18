#include "dxpch.h"

#include "Renderer.h"
#include "Renderer3D.h"

namespace Dunix {

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer3D::Init();
	}

	void Renderer::BeginScene(const Camera& camera)
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(VertexArray* vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}