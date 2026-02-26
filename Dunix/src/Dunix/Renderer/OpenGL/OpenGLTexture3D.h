#pragma once

#include "Dunix/Renderer/Texture.h"
#include <glad/glad.h>

namespace Dunix {
	class OpenGLTexture3D : public Texture3D
	{
	public:
		OpenGLTexture3D(uint32_t width, uint32_t height);
		OpenGLTexture3D(const std::string& path);

		virtual ~OpenGLTexture3D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}

