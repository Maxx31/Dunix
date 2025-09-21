#pragma once

#ifdef DX_PLATFORM_WINDOWS 

extern Dunix::Application* Dunix::CreateApplication();

int main(int argc, char** argv)
{
	Dunix::Log::Init();

	auto app = Dunix::CreateApplication();
	app->Run();
	delete app;
}
#endif