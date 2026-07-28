#include "dxpch.h"
#include "AssetManager.h"

#include "ModelImporter.h"

namespace Dunix
{
    SharedPtr<Model> AssetManager::LoadModel(const std::string& inFilename)
    {
        static std::unordered_map<std::string, WeakPtr<Model>> loadedModels;

        if (auto it = loadedModels.find(inFilename); it != loadedModels.end())
        {
            //If model is already loaded
            if (SharedPtr<Model> model = it->second.lock())
                return model;
        }

        SharedPtr<Model> model = ModelImporter::LoadModel(inFilename);
        
        if (model)
        {
            loadedModels[inFilename] = model;
        }

        return model;
    }
}
