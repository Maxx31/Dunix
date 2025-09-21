#include <Dunix.h>

class Sandbox : public Dunix::Application
{
public:
	Sandbox()
	{
		PushOverlay(new Dunix::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Dunix::Application* Dunix::CreateApplication()
{
	return new Sandbox();
}