#pragma once
#include "Dunix/Renderer/Buffer.h"

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
    
    private:
        SharedPtr<Dunix::VertexArray> m_VertexArray;
        SharedPtr<VertexBuffer> m_VertexBuffer;
        SharedPtr<IndexBuffer> m_IndexBuffer;
    };
}
