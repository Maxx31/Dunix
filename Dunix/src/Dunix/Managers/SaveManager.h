#pragma once

#include "Dunix/Core/Core.h"
#include "Dunix/Core/Log.h"
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

namespace Dunix
{
    class DUNIX_API SaveManager
    {
    public:
        SaveManager();
        virtual ~SaveManager();
        
        nlohmann::json ConvertSceneToJson(SharedPtr<class Scene> Scene);
        SharedPtr<class Scene> ConvertJsonToScene(nlohmann::json Json);
        
        static SaveManager& Get()
        {
            if (!m_Instance){ DX_CORE_ERROR("Save manager instance is null!");} 
            return *m_Instance;
        }

    private:
        static SaveManager* m_Instance;
        
        std::string m_ProjectPath;
        bool m_ProjectSelected = false;
    };

    inline std::unique_ptr<SaveManager> CreateSaveManager()
    {
        return std::make_unique<SaveManager>();
    }
}
