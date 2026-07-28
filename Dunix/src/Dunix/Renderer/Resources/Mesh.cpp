#include "dxpch.h"
#include "Mesh.h"

#include <assimp/mesh.h>

namespace Dunix
{
    static MeshData CreateMeshDataFromAssimp(const aiMesh* inAiMesh)
    {
        MeshData result;
        result.Layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoord" }
        };

        result.Vertices.reserve(inAiMesh->mNumVertices * 5); //3 For position and 2 for tex coord
        for (unsigned int i = 0; i < inAiMesh->mNumVertices; i++)
        {
            const aiVector3D& vertex = inAiMesh->mVertices[i];
            const aiVector3D texCoord = inAiMesh->HasTextureCoords(0) ? inAiMesh->mTextureCoords[0][i] : aiVector3D(0.0f);

            result.Vertices.push_back(vertex.x);
            result.Vertices.push_back(vertex.y);
            result.Vertices.push_back(vertex.z);
            result.Vertices.push_back(texCoord.x);
            result.Vertices.push_back(texCoord.y);
        }

        for (unsigned int i = 0; i < inAiMesh->mNumFaces; i++)
        {
            const aiFace& face = inAiMesh->mFaces[i];
            for (unsigned int index = 0; index < face.mNumIndices; index++)
                result.Indices.push_back(face.mIndices[index]);
        }

        return result;
    }

    Mesh::Mesh(const MeshData& inMeshData)
    {
        if (inMeshData.Vertices.empty() || inMeshData.Indices.empty())
        {
            DX_CORE_WARN("Tried to create an empty mesh.");
            return;
        }

        m_VertexBuffer = VertexBuffer::Create(inMeshData.Vertices.data(), static_cast<uint32_t>(inMeshData.Vertices.size() * sizeof(float)));
        m_VertexBuffer->SetLayout(inMeshData.Layout);

        m_IndexBuffer = IndexBuffer::Create(inMeshData.Indices.data(), static_cast<uint32_t>(inMeshData.Indices.size()));

        m_VertexArray = VertexArray::Create();
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
    }

    Mesh::Mesh(const aiMesh* inAiMesh)
        : Mesh(CreateMeshDataFromAssimp(inAiMesh))
    {
    }

    uint32_t Mesh::GetIndexCount() const
    {
        return m_IndexBuffer ? m_IndexBuffer->GetCount() : 0;
    }
}
