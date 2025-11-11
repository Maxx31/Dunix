#pragma once
#include <cstdint>

namespace Dunix
{
	class VertexBuffer
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t  size);
	};

	class IndexBuffer {
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(const uint32_t* indices, uint32_t  count);
	};

	class VertexArray
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVertexBuffer(VertexBuffer* vb) = 0;
		virtual void SetIndexBuffer(IndexBuffer* ib) = 0;

		static VertexArray* Create();
	};

}