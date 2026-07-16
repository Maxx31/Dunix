#include "dxpch.h"
#include "Scene.h"

#include "Components.h"
#include "Entity.h"
#include "Dunix/Renderer/Camera.h"
#include "Dunix/Renderer/Renderer3D.h"
#include "Dunix/Renderer/Texture.h"

namespace Dunix
{
    Scene::Scene(entt::registry* registry)
    {
        if (registry)
            m_Registry = std::move(*registry);
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity()
    {
        Entity entity = { m_Registry.create(), this };
        return entity;
    }

    void Scene::DestroyEntity(entt::entity inEntity)
    {
        m_Registry.destroy(inEntity);
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

            if (cube.Texture)
                Renderer3D::DrawCube(transform.Position, transform.Scale, cube.Texture);
            else
                Renderer3D::DrawCube(transform.Position, transform.Scale, cube.Color);
        }

        Renderer3D::EndScene();
    }
}
