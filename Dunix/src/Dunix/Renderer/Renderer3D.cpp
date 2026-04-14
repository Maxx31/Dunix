#include "dxpch.h"
#include "Renderer3D.h"
#include "Texture.h"

#include "Buffer.h"
#include "Shader.h"
#include "Camera.h"

namespace Dunix {

	struct Renderer3DStorage
	{
		VertexArray* CubeVertexArray;
        Shader* TextureShader;
        Texture3D* WhiteTexture;
	};

	static Renderer3DStorage* m_Data;

	void Renderer3D::Init()
	{
        ProfileScope scope("Renderer3D::Init");
        m_Data = new Renderer3DStorage();

        //Rendering simple cube 
        float CubeVertices[] =
        {
            // x, y, z, texCoords (x, y, z)
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, // 0
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // 1
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // 2
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // 3
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, // 4
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // 5
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // 6
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f // 7
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

        CubeVB = VertexBuffer::Create(CubeVertices, sizeof(CubeVertices));
        CubeVB->SetLayout({
            { ShaderDataType::Float3, "aPos" },  // 3 floats: x, y, z
            { ShaderDataType::Float3, "a_TexCoord" }
            });

        CubeIB = IndexBuffer::Create(indices, 36);
        m_Data->CubeVertexArray = VertexArray::Create();

        m_Data->CubeVertexArray->AddVertexBuffer(CubeVB);
        m_Data->CubeVertexArray->SetIndexBuffer(CubeIB);

        m_Data->WhiteTexture = Texture3D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        m_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        m_Data->TextureShader = Shader::CreateFromFile(
            "assets/shaders/Texture.vert",
            "assets/shaders/Texture.frag"
        );
        m_Data->TextureShader->Bind();
        m_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer3D::Shutdown()
	{
        delete m_Data;
	}

	void Renderer3D::BeginScene(const Camera& camera)
	{
        m_Data->TextureShader->Bind();
        m_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjection());
	}

	void Renderer3D::EndScene()
	{

	}

	void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
	{
        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, position);
        transform = glm::scale(transform, size);

        // Shader MUST be bound before setting uniforms
        m_Data->TextureShader->Bind();
        m_Data->TextureShader->SetMat4("u_Transform", transform);
        m_Data->TextureShader->SetFloat4("u_Color", color);

        m_Data->WhiteTexture->Bind();
        m_Data->CubeVertexArray->Bind();

        RenderCommand::DrawIndexed(m_Data->CubeVertexArray);
	}

    void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& size, const Texture3D* texture)
    {
        ProfileScope scope("Renderer3D::DrawCube");
        m_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, size.z });
        m_Data->TextureShader->SetMat4("u_Transform", transform);

        m_Data->CubeVertexArray->Bind();
        RenderCommand::DrawIndexed(m_Data->CubeVertexArray);
    }
}