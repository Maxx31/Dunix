#include "dxpch.h"
#include "Shader.h"
#include "OpenGL/OpenGLShader.h"

namespace Dunix
{
	SharedPtr<Shader> Shader::CreateFromFile(const std::string& vsPath, const std::string fsPath)
	{
		return std::make_shared<OpenGLShader>(vsPath, fsPath);
	}

}
