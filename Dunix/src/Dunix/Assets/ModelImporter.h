#pragma once

namespace Dunix
{
    class Model;
    
    class ModelImporter
    {
    public:
        static Model* LoadModel(const std::string &inFilename);
    };
}
