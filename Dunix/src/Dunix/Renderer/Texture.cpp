#include "dxpch.h"

#include "Dunix/Renderer/OpenGL/OpenGLTexture3D.h"
#include "Dunix/Renderer/Texture.h"

namespace Dunix {

	SharedPtr<Texture3D> Texture3D::Create(uint32_t width, uint32_t height)
	{
		return std::make_shared<OpenGLTexture3D>(width, height);
	}

	SharedPtr<Texture3D> Texture3D::Create(const std::string& path)
	{
		return std::make_shared<OpenGLTexture3D>(path);
	}

}
