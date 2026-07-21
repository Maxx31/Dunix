#include "dxpch.h"
#include "Model.h"
#include "Mesh.h"

#include <assimp/scene.h>

namespace Dunix
{
    Model::Model(std::vector<UniquePtr<Mesh>> meshes)
        : Meshes(std::move(meshes))
    {
    }

    Model::Model(const aiScene* inScene)
    {
        for (unsigned int i = 0; i < inScene->mNumMeshes; i++)
        {
            const aiMesh* paiMesh = inScene->mMeshes[i];
            Meshes.push_back(std::make_unique<Mesh>(paiMesh));
        }
    }

    void Model::AddNewMesh(UniquePtr<Mesh> inMesh)
    {
        Meshes.push_back(std::move(inMesh));
    }
}
