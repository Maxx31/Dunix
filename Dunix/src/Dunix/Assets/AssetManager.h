#pragma once

namespace Dunix
{
    class Model;
    
    class AssetManager
    {
    public:
        static Model* LoadModel(const std::string &inFilename);
    };
}
