#pragma once

#include <cstdint>
#include <string>

namespace Dunix
{
    struct ImportedModelInfo
    {
        bool IsValid = false;
        std::string Error;

        uint32_t MeshCount = 0;
        uint32_t MaterialCount = 0;
        uint32_t AnimationCount = 0;
        uint32_t TotalVertexCount = 0;
        uint32_t TotalIndexCount = 0;
    };

    class ModelImporter
    {
    public:
        static ImportedModelInfo Inspect(const std::string& path);
    };
}
