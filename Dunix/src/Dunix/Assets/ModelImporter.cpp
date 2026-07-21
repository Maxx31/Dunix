#include "dxpch.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Dunix/Renderer/Resources/Model.h"

#include "ModelImporter.h"

namespace Dunix
{
    Model* ModelImporter::LoadModel(const std::string &inFilename)
    {
        Assimp::Importer Importer;
        
        const aiScene* scene = Importer.ReadFile(inFilename.c_str(), 
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_GenSmoothNormals |
        aiProcess_CalcTangentSpace |
        aiProcess_FlipUVs
        );
        
        if (scene)
        {
            Model* model = new Model(scene);
            return model;
        }
        else
        {
            DX_CORE_ERROR("Error loading model '{0}' : '{1}", inFilename.c_str(), Importer.GetErrorString());
        }
        return false;
    }
}
