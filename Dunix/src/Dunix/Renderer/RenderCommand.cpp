#include "dxpch.h"
#include "RenderCommand.h"

namespace Dunix {
	SharedPtr<RendererAPI> RenderCommand::m_RendererAPI = RendererAPI::Create();
}
