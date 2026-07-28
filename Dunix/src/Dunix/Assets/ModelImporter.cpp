#include "dxpch.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Dunix/Renderer/Resources/Model.h"

#include "ModelImporter.h"

namespace Dunix
{
    SharedPtr<Model> ModelImporter::LoadModel(const std::string& inFilename)
    {
        Assimp::Importer importer;
        
        const aiScene* scene = importer.ReadFile(inFilename.c_str(), 
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_GenSmoothNormals |
            aiProcess_CalcTangentSpace |
            aiProcess_FlipUVs
        );
        
        if (scene && scene->mRootNode)
            return std::make_shared<Model>(scene);

        DX_CORE_ERROR("Error loading model '{0}': '{1}'", inFilename.c_str(), importer.GetErrorString());
        return nullptr;
    }
}
