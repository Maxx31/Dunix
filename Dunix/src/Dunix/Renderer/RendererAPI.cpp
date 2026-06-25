#include "dxpch.h"
#include "RendererAPI.h"
#include "Dunix/Renderer/OpenGL/OpenGLRendererAPI.h"

namespace Dunix {

	SharedPtr<RendererAPI> RendererAPI::Create()
	{	
		return std::make_shared<OpenGLRendererAPI>();
	}
}
