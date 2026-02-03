#include <Dunix.h>
#include "EditorLayer.h"

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

		virtual void OnImGuiRender() override
		{
			ImGui::Begin("Test");
			ImGui::Text("Hello World");
			ImGui::End();
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
			PushLayer(new EditorLayer());
		}

		~Editor()
		{

		}
	};
	Application* CreateApplication()
	{
		return new Editor();
	}
}