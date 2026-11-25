#include <Dunix.h>
#include "EditorLayer.h"
#include "Dunix/Managers/ProjectManager.h"
#include "Dunix/Managers/SaveManager.h"

//--------EntryPoint--------------
#include "Dunix/Core/EntryPoint.h"
//----------------------------

#include <imgui/imgui.h>

namespace Dunix
{
	class ExampleLayer : public Layer
	{
	public:
		ExampleLayer()
			: Layer("Example")
		{
		}

		void OnEvent(Event& event) override
		{
		}

	};

	class Editor : public Application
	{
	public:
		Editor()
		{
			PushLayer<EditorLayer>();
		}

		~Editor()
		{

		}

	private:
		std::unique_ptr<ProjectManager> m_ProjectManager = CreateProjectManager();
		std::unique_ptr<SaveManager> m_SaveManager = CreateSaveManager();
	};
	
	std::unique_ptr<Application> CreateApplication()
	{
		return std::make_unique<Editor>();
	}
}
