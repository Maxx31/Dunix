#include "dxpch.h"
#include "Mesh.h"

#include <assimp/mesh.h>

namespace Dunix
{
    Mesh::Mesh(const aiMesh* inAiMesh)
    {
        for (unsigned int i = 0; i < inAiMesh->mNumVertices; i++)
        {
            const aiVector3D& Vertex = inAiMesh->mVertices[i];
            const aiVector3D& Normal = inAiMesh->mNormals[i];
            const aiVector3D& TexCoord = inAiMesh->HasTextureCoords(0) ? inAiMesh->mTextureCoords[0][i] : aiVector3D(0.0f, 0.0f, 0.0f);
            
            //Need to find a way to promote it to our Mesh properly
            m_VertexArray = VertexArray::Create(); 
        }
    }
}
