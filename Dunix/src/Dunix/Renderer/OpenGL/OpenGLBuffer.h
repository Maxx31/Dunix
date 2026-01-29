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

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(VertexBuffer* vb) override;
		virtual void SetIndexBuffer(IndexBuffer* ib) override;

		virtual const IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		unsigned int m_VAO;

		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer = nullptr;
	};
}