#include "dxpch.h"
#include "AssetManager.h"

#include "ModelImporter.h"

namespace Dunix
{
    Model* AssetManager::LoadModel(const std::string &inFilename)
    {
        return ModelImporter::LoadModel(inFilename);
    }
}
