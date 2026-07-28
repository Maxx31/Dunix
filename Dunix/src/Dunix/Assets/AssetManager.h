#pragma once

#include "Dunix/Core/Core.h"

#include <string>

namespace Dunix
{
    class Model;
    
    class AssetManager
    {
    public:
        static SharedPtr<Model> LoadModel(const std::string &inFilename);
    };
}
