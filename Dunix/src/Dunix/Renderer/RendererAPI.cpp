#include "dxpch.h"
#include "RendererAPI.h"
#include "Dunix/Renderer/OpenGL/OpenGLRendererAPI.h"

namespace Dunix {

	RendererAPI* RendererAPI::Create()
	{	
		auto CurrentRenderAPI = new OpenGLRendererAPI();

		return CurrentRenderAPI;
	}
}