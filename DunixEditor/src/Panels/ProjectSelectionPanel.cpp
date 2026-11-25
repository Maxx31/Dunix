#include "dxpch.h"
#include "ProjectSelectionPanel.h"

#include "Dunix/Managers/ProjectManager.h"
#include "imgui/imgui.h"

namespace Dunix
{
    ProjectSelectionPanel::ProjectSelectionPanel()
    {
    }

    void ProjectSelectionPanel::OnImGuiRender()
    {
        ImGui::Begin("Project Selection");
        
        if (ImGui::Button("Create Project"))
        {
            //Didn't find build-in Imgui way of opening directory selection
            //In here need to open input window for user to enter name of project, in the future full path and open explorer window
            ProjectManager::Get().CreateProjectInLocalPathWithName("DunixProject");
        }
        if (ImGui::Button("Open Project"))
        {   
            //Here need to add a full UI with all available project
            if (ImGui::BeginPopupModal("ThePopup")) {
                // Draw popup contents.
                ImGui::EndPopup();
            }
            ProjectManager::Get().OpenProjectWithLocalPath("Test");
        }
        
        ImGui::End();
    }
}
