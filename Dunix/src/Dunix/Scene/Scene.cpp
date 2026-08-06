#include "dxpch.h"
#include "Scene.h"

#include "Components.h"
#include "Entity.h"
#include "Dunix/Renderer/Camera.h"
#include "Dunix/Renderer/Renderer3D.h"
#include "Dunix/Renderer/Texture.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Dunix
{
    static glm::mat4 GetTransform(const TransformComponent& transform)
    {
        glm::mat4 result = glm::mat4(1.0f);
        result = glm::translate(result, transform.Position);
        result = glm::rotate(result, glm::radians(transform.Rotation.x), { 1.0f, 0.0f, 0.0f });
        result = glm::rotate(result, glm::radians(transform.Rotation.y), { 0.0f, 1.0f, 0.0f });
        result = glm::rotate(result, glm::radians(transform.Rotation.z), { 0.0f, 0.0f, 1.0f });
        result = glm::scale(result, transform.Scale);
        return result;
    }

    Scene::Scene(entt::registry* registry)
    {
        if (registry)
            m_Registry = std::move(*registry);
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity(const std::string& InName)
    {
        return CreateEntityWithUUID(UUID(), InName);
    }

    Entity Scene::CreateEntityWithUUID(UUID id, const std::string& InName)
    {
        Entity entity = { m_Registry.create(), this };
        
        //Default components for every entity
        entity.AddComponent<IDComponent>(id);
        entity.AddComponent<TagComponent>(InName);
        entity.AddComponent<TransformComponent>();

        return entity;
    }

    Entity Scene::DuplicateEntity(Entity entity)
    {
        if (!entity)
            return {};

        Entity newEntity = CreateEntity(entity.GetEntityName());

        if (entity.HasComponent<TransformComponent>())
            newEntity.GetComponent<TransformComponent>() = entity.GetComponent<TransformComponent>();

        if (entity.HasComponent<CubeRendererComponent>())
            newEntity.AddComponent<CubeRendererComponent>(entity.GetComponent<CubeRendererComponent>());

        if (entity.HasComponent<MeshRendererComponent>())
            newEntity.AddComponent<MeshRendererComponent>(entity.GetComponent<MeshRendererComponent>());

        return newEntity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        if (!entity)
            return;

        m_Registry.destroy(entity.GetHandle());
    }

    void Scene::OnUpdate(Timestep ts)
    {
        // Scene update systems will go here, for example physics or scripted movement.
    }

    void Scene::OnRender(const Camera& camera)
    {
        Renderer3D::BeginScene(camera);

        auto view = m_Registry.view<TransformComponent, CubeRendererComponent>();
        for (auto entity : view)
        {
            auto& transform = view.get<TransformComponent>(entity);
            auto& cube = view.get<CubeRendererComponent>(entity);
            int entityID = static_cast<int>(entity);

            if (cube.Texture)
                Renderer3D::DrawCube(transform.Position, transform.Scale, cube.Texture, entityID);
            else
                Renderer3D::DrawCube(transform.Position, transform.Scale, cube.Color, entityID);
        }

        auto meshView = m_Registry.view<TransformComponent, MeshRendererComponent>();
        for (auto entity : meshView)
        {
            auto& transform = meshView.get<TransformComponent>(entity);
            auto& meshRenderer = meshView.get<MeshRendererComponent>(entity);
            int entityID = static_cast<int>(entity);

            if (meshRenderer.ModelAsset)
                Renderer3D::DrawModel(*meshRenderer.ModelAsset, GetTransform(transform), meshRenderer.Color, entityID);
        }

        Renderer3D::EndScene();
    }
}
