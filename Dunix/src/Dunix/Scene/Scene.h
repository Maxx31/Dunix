#pragma once

#include "Dunix/Core/Timestep.h"
#include <entt.hpp>

namespace Dunix
{
    
    class Entity;
    
    class Scene
    {
    public:
        Scene() = default;
        Scene(entt::registry* registry);
        ~Scene();
        
         entt::registry* GetEnttRegistry() const
         {
             return m_Registry;
         }
    
        Entity CreateEntity();
        void DestroyEntity(entt::entity inEntity);
        
        void OnUpdate(Timestep ts);
        
    private:
        entt::registry* m_Registry;
    };
}
