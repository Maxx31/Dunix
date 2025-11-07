#pragma once
#include <cstdint>
#include "Dunix/Renderer/Buffer.h"
#include <glad/glad.h>

namespace Dunix
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const float* vertices, uint32_t size);

		void Bind() const override;
		void Unbind() const override;

	private:
		GLuint m_RendererID = 0;
	};

	class OpenGLIndexBuffer : public IndexBuffer 
	{
	public:
		OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);


		void Bind() const override;
		void Unbind() const override;

	private:
		GLuint m_ID = 0;
	};

}