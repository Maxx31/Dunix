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
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		GLuint m_RendererID = 0;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer 
	{
	public:
		OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;

		uint32_t GetCount() const override { return m_Count;}

	private:
		GLuint m_ID = 0;
		uint32_t m_Count = 0;
	};

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const SharedPtr<VertexBuffer>& vb) override;
		virtual void SetIndexBuffer(const SharedPtr<IndexBuffer>& ib) override;

		virtual const SharedPtr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

	private:
		unsigned int m_VAO;

		std::vector<SharedPtr<VertexBuffer>> m_VertexBuffers;
		SharedPtr<IndexBuffer> m_IndexBuffer;
	};
}
