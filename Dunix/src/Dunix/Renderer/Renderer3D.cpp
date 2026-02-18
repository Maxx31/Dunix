#include "dxpch.h"
#include "Renderer3D.h"

#include "Buffer.h"
#include "Shader.h"
#include "Camera.h"

namespace Dunix {

	struct Renderer3DStorage
	{
		VertexArray* CubeVertexArray;
		Shader* BasicShader;
	};

	static Renderer3DStorage* m_Data;

	void Renderer3D::Init()
	{
        m_Data = new Renderer3DStorage();

        //Rendering simple cube 
        float vertices[] =
        {
            // x, y, z
            -0.5f, -0.5f, -0.5f, // 0
             0.5f, -0.5f, -0.5f, // 1
             0.5f,  0.5f, -0.5f, // 2
            -0.5f,  0.5f, -0.5f, // 3
            -0.5f, -0.5f,  0.5f, // 4
             0.5f, -0.5f,  0.5f, // 5
             0.5f,  0.5f,  0.5f, // 6
            -0.5f,  0.5f,  0.5f  // 7
        };

        uint32_t indices[] =
        {
            // back face (-Z)
            0, 1, 2,  2, 3, 0,
            // front face (+Z)
            4, 5, 6,  6, 7, 4,
            // left face (-X)
            4, 7, 3,  3, 0, 4,
            // right face (+X)
            1, 5, 6,  6, 2, 1,
            // bottom face (-Y)
            4, 5, 1,  1, 0, 4,
            // top face (+Y)
            3, 2, 6,  6, 7, 3
        };

        VertexBuffer* CubeVB;
        IndexBuffer* CubeIB;

        CubeVB = VertexBuffer::Create(vertices, sizeof(vertices));
        CubeVB->SetLayout({
            { ShaderDataType::Float3, "aPos" }   // 3 floats: x, y, z
            });

        CubeIB = IndexBuffer::Create(indices, 36);
        m_Data->CubeVertexArray = VertexArray::Create();

        m_Data->CubeVertexArray->AddVertexBuffer(CubeVB);
        m_Data->CubeVertexArray->SetIndexBuffer(CubeIB);

        m_Data->BasicShader = Shader::CreateFromFile(
            "assets/shaders/default.vert",
            "assets/shaders/default.frag"
        );
	}

	void Renderer3D::Shutdown()
	{
        delete m_Data;
	}

	void Renderer3D::BeginScene(const Camera& camera)
	{
        m_Data->BasicShader->Bind();
        m_Data->BasicShader->SetMat4("u_ViewProjection", camera.GetViewProjection());
        m_Data->BasicShader->SetMat4("u_Transform", glm::mat4(1.0));
	}

	void Renderer3D::EndScene()
	{

	}

	void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
	{
        m_Data->BasicShader->Bind();

        m_Data->CubeVertexArray->Bind();
        RenderCommand::DrawIndexed(m_Data->CubeVertexArray);
	}
}