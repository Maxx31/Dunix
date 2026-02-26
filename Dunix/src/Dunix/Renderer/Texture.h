#pragma once

namespace Dunix{
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
	};

	class Texture3D : public Texture
	{
	public:
		static Texture3D* Create(uint32_t width, uint32_t height);
		static Texture3D* Create(const std::string& path);
	};
}

