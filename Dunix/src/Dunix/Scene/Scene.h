#pragma once

#include "Dunix/Core/Timestep.h"
#include "Dunix/Utils/UUID.h"
#include <entt.hpp>

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
        
        std::unordered_map<UUID, Entity>& GetAllEntites(){return m_Entities;}
    
        Entity CreateEntity(const std::string& InName = "Entity");
        void DestroyEntity(Entity* InEntity);
        
        void OnUpdate(Timestep ts);
        void OnRender(const Camera& camera);
        
    private:
        std::unordered_map<UUID, Entity> m_Entities;
        entt::registry m_Registry;
    };
}
