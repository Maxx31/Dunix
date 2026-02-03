#include <Dunix.h>
#include <imgui/imgui.h>

//--------EntryPoint--------------
#include "Dunix/Core/EntryPoint.h"
//----------------------------

class ExampleLayer : public Dunix::Layer
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

	void OnEvent(Dunix::Event& event) override
	{
	}

};

class Editor : public Dunix::Application
{
public:
	Editor()
	{
		PushLayer(new ExampleLayer());
	}

	~Editor()
	{

	}
};

Dunix::Application* Dunix::CreateApplication()
{
	return new Editor();
}