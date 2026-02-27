#include "dxpch.h"

#include "Dunix/Renderer/OpenGL/OpenGLTexture3D.h"
#include "Dunix/Renderer/Texture.h"

namespace Dunix {

	Texture3D* Texture3D::Create(uint32_t width, uint32_t height)
	{
		return new OpenGLTexture3D(width, height);
	}

	Texture3D* Texture3D::Create(const std::string& path)
	{
		return new OpenGLTexture3D(path);
	}

}