#pragma once

#include "Dunix/Core/Core.h"
#include "Dunix/Core/Log.h"
#include <memory>
#include <string>
#include <vector>

namespace Dunix
{
    class DUNIX_API ProjectManager
    {
    public:
        ProjectManager();
        virtual ~ProjectManager();
        
        std::vector<std::string> GetAllProjects();
        
        void CreateProjectInLocalPathWithName(std::string name, std::string projectPath = " ");
        void OpenProjectWithLocalPath(const std::string& path);
        
        bool IsProjectSelected() const {return m_ProjectSelected;}
        
        std::string GetProjectFiles();
        
        std::string GetProjectPath() {return m_ProjectPath;}
        void SetProjectPath(const std::string& inProjectPath);
        void CreateFolder(const std::string& inName);

        static ProjectManager& Get()
        {
            if (!m_Instance){ DX_CORE_ERROR("Project manager instance is null!");} 
            return *m_Instance;
        }

    private:
        static ProjectManager* m_Instance;
        
        std::string m_ProjectPath;
        bool m_ProjectSelected = false;
    };

    inline std::unique_ptr<ProjectManager> CreateProjectManager()
    {
        return std::make_unique<ProjectManager>();
    }
}
