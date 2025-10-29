#include <Dunix.h>

#include <imgui/imgui.h>

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

class Sandbox : public Dunix::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Dunix::Application* Dunix::CreateApplication()
{
	return new Sandbox();
}