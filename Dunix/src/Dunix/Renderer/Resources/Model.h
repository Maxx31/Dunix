#pragma once

struct aiScene;
namespace Dunix
{
    class Mesh;
    
    class Model
    {
    public:
        Model() = default;
        explicit Model(std::vector<UniquePtr<Mesh>> inMeshes);
        explicit Model(const aiScene* inScene);
        
        void AddNewMesh(UniquePtr<Mesh>inMesh);
        
    private:
        std::vector<UniquePtr<Mesh>> Meshes;
    };
}
