#pragma once

#include "Core.h"

namespace Dunix
{
	class DUNIX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
