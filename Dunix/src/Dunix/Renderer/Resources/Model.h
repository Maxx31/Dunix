#pragma once

#include "Dunix/Core/Core.h"

#include <vector>

struct aiScene;

namespace Dunix
{
    class Mesh;
    
    class Model
    {
    public:
        Model() = default;
        ~Model();

        explicit Model(std::vector<UniquePtr<Mesh>> inMeshes);
        explicit Model(const aiScene* inScene);
        
        void AddNewMesh(UniquePtr<Mesh> inMesh);
        const std::vector<UniquePtr<Mesh>>& GetMeshes() const { return Meshes; }
        
    private:
        std::vector<UniquePtr<Mesh>> Meshes;
    };
}
