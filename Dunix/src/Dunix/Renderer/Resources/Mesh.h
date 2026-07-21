#pragma once

#include "Dunix/Renderer/Buffer.h"

struct aiMesh;

namespace Dunix
{
    struct MeshData
    {
        std::vector<float> Vertices;
        std::vector<uint32_t> Indices;
        BufferLayout Layout;
    };
    
    class Mesh
    {
    public:
        Mesh(const MeshData& inMeshData);
        Mesh(const aiMesh* inAiMesh);
    
    private:
        SharedPtr<VertexArray> m_VertexArray;
        SharedPtr<VertexBuffer> m_VertexBuffer;
        SharedPtr<IndexBuffer> m_IndexBuffer;
    };
}
