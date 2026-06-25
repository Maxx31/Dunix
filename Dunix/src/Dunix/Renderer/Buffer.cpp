#include "dxpch.h"
#include "Buffer.h"
#include "OpenGL/OpenGLBuffer.h"

namespace Dunix
{
	SharedPtr<VertexBuffer> VertexBuffer::Create(const float* vertices, uint32_t size)
	{
		return std::make_shared<OpenGLVertexBuffer>(vertices, size);
	}

	SharedPtr<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, uint32_t count)
	{
		return std::make_shared<OpenGLIndexBuffer>(indices, count);
	}

	SharedPtr<VertexArray> VertexArray::Create()
	{
		return std::make_shared<OpenGLVertexArray>();
	}
}
