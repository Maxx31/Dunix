#include "dxpch.h"
#include "Buffer.h"
#include "OpenGL/OpenGLBuffer.h"

namespace Dunix
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		return new OpenGLVertexBuffer(vertices, size);
	}

	IndexBuffer* IndexBuffer::Create(const uint32_t* indices, uint32_t count)
	{
		return new OpenGLIndexBuffer(indices, count);
	}
}