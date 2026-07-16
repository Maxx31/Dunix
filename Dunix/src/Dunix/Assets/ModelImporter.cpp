#include "dxpch.h"
#include "ModelImporter.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4251)
#endif

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

namespace Dunix
{
    ImportedModelInfo ModelImporter::Inspect(const std::string& path)
    {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(
            path,
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_GenSmoothNormals |
            aiProcess_CalcTangentSpace |
            aiProcess_ImproveCacheLocality |
            aiProcess_ValidateDataStructure
        );

        ImportedModelInfo info;
        if (!scene || !scene->mRootNode)
        {
            info.Error = importer.GetErrorString();
            return info;
        }

        info.IsValid = true;
        info.MeshCount = scene->mNumMeshes;
        info.MaterialCount = scene->mNumMaterials;
        info.AnimationCount = scene->mNumAnimations;

        for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++)
        {
            const aiMesh* mesh = scene->mMeshes[meshIndex];
            info.TotalVertexCount += mesh->mNumVertices;

            for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++)
                info.TotalIndexCount += mesh->mFaces[faceIndex].mNumIndices;
        }

        return info;
    }
}
