#include "dxpch.h"
#include "Shader.h"
#include "OpenGL/OpenGLShader.h"

namespace Dunix
{
	Shader* Shader::CreateFromFile(const std::string& vsPath, const std::string fsPath)
	{
		return new OpenGLShader(vsPath, fsPath);
	}

}
