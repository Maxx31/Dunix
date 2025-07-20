#include <Dunix.h>

class Sandbox : public Dunix::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Dunix::Application* Dunix::CreateApplication()
{
	return new Sandbox();
}