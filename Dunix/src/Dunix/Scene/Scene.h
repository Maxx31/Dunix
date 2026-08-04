#pragma once

#include "Dunix/Core/Timestep.h"
#include "Dunix/Utils/UUID.h"
#include <entt.hpp>
#include <string>

namespace Dunix
{
    
    class Entity;
    class Camera;
    
    class Scene
    {
    public:
        Scene() = default;
        Scene(entt::registry* registry);
        ~Scene();
        
        entt::registry& GetEnttRegistry()
        {
            return m_Registry;
        }

        const entt::registry& GetEnttRegistry() const
        {
            return m_Registry;
        }

        Entity CreateEntity(const std::string& InName = "Entity");
        Entity CreateEntityWithUUID(UUID id, const std::string& InName = "Entity");
        Entity DuplicateEntity(Entity entity);
        void DestroyEntity(Entity entity);
        
        void OnUpdate(Timestep ts);
        void OnRender(const Camera& camera);
        
    private:
        entt::registry m_Registry;
    };
}
