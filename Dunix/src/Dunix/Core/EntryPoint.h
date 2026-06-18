#pragma once

#ifdef DX_PLATFORM_WINDOWS 

extern std::unique_ptr<Dunix::Application> Dunix::CreateApplication();

int main(int argc, char** argv)
{
	Dunix::Log::Init();

	auto app = Dunix::CreateApplication();
	app->Run();
}
#endif