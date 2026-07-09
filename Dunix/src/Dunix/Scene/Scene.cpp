#include "dxpch.h"
#include "Scene.h"

#include "Componentns.h"
#include "Entity.h"

namespace Dunix
{
    Scene::Scene(entt::registry* registry)
    {
        m_Registry = registry;
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity()
    {
        Entity entity = { m_Registry->create(), this };
        return entity;
    }

    void Scene::DestroyEntity(entt::entity inEntity)
    {
        m_Registry->destroy(inEntity);
    }

    void Scene::OnUpdate(Timestep ts)
    {
        //Transform handling
        auto view = m_Registry->view<TransformComponent>();
        for (auto entity : view)
        {
            //Update something here. Howerver would be good to have some system doing it
        }
    }
}
