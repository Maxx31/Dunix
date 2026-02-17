#include "dxpch.h"
#include "Renderer3D.h"

#include "Buffer.h"
#include "Shader.h"

namespace Dunix {

	struct Renderer3DStorage
	{
		VertexArray* VertexArray;
		Shader* BasicShader;
	};

	static Renderer3DStorage m_Data;

	void Renderer3D::Init()
	{

	}

	void Renderer3D::Shutdown()
	{

	}

	void Renderer3D::BeginScene()
	{

	}

	void Renderer3D::EndScene()
	{

	}

	void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
	{

	}
}