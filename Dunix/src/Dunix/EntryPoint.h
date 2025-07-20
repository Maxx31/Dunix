#pragma once

#ifdef DX_PLATFORM_WINDOWS 

extern Dunix::Application* Dunix::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Dunix::CreateApplication();
	app->Run();
	delete app;
}

#endif