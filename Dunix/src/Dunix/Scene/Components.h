#pragma once

#include "Dunix/Core/Core.h"
#include "Dunix/Utils/UUID.h"
#include <glm/glm.hpp>
#include <string>

namespace Dunix
{
    struct IdComponent
    {
        IdComponent() = default;
        IdComponent(const UUID& id)
            : Id(id){};

        UUID Id;
    };
    
    struct TagComponent
    {
        TagComponent() = default;
        TagComponent(const std::string& InName) 
            :Name(InName){};

        std::string Name;
    };
    
    struct TransformComponent
    {
        TransformComponent() = default;
        TransformComponent(const glm::vec3& position)
            : Position(position) {}
        TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
            : Position(position), Rotation(rotation), Scale(scale) {}

        glm::vec3 Position{ 0.0f };
        glm::vec3 Rotation{ 0.0f };
        glm::vec3 Scale{ 1.0f };
    };

    struct CubeRendererComponent
    {
        CubeRendererComponent() = default;
        CubeRendererComponent(const glm::vec4& color)
            : Color(color) {}
        CubeRendererComponent(const glm::vec4& color, const class Texture3D* texture)
            : Color(color), Texture(texture) {}

        glm::vec4 Color{ 1.0f };
        const class Texture3D* Texture = nullptr;
    };

    struct MeshRendererComponent
    {
        MeshRendererComponent() = default;
        MeshRendererComponent(const SharedPtr<class Model>& model)
            : ModelAsset(model) {}
        MeshRendererComponent(const SharedPtr<class Model>& model, const glm::vec4& color)
            : ModelAsset(model), Color(color) {}

        SharedPtr<class Model> ModelAsset = nullptr;
        glm::vec4 Color{ 1.0f };
    };
}
