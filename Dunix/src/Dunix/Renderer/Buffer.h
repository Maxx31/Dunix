#pragma once
#include <cstdint>

namespace Dunix
{
	///////////////////////MISC/////////////////////////////////////////
	enum class ShaderDataType { None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type) {
		case ShaderDataType::Float:  return 4;
		case ShaderDataType::Float2: return 8;
		case ShaderDataType::Float3: return 12;
		case ShaderDataType::Float4: return 16;
		case ShaderDataType::Mat3:   return 36;
		case ShaderDataType::Mat4:   return 64;
		case ShaderDataType::Int:    return 4;
		case ShaderDataType::Int2:   return 8;
		case ShaderDataType::Int3:   return 12;
		case ShaderDataType::Int4:   return 16;
		case ShaderDataType::Bool:   return 1;
		default: return 0;
		}
	}
	//TODO: Implement buffer layout

	class VertexBuffer
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

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
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(VertexBuffer* vb) = 0;
		virtual void SetIndexBuffer(IndexBuffer* ib) = 0;

		static VertexArray* Create();
	};

}