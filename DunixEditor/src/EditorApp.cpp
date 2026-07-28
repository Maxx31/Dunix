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
	};
	
	std::unique_ptr<Application> CreateApplication()
	{
		return std::make_unique<Editor>();
	}
}