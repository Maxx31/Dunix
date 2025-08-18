#include "Core.h"

#include "spdlog/spdlog.h"

#pragma once

#define DX_CORE_TRACE(...)    ::Dunix::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DX_CORE_INFO(...)     ::Dunix::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DX_CORE_WARN(...)     ::Dunix::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DX_CORE_ERROR(...)    ::Dunix::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DX_CORE_FATAL(...)    ::Dunix::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define DX_TRACE(...)	      ::Dunix::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DX_INFO(...)	      ::Dunix::Log::GetClientLogger()->info(__VA_ARGS__)
#define DX_WARN(...)	      ::Dunix::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DX_ERROR(...)	      ::Dunix::Log::GetClientLogger()->error(__VA_ARGS__)
#define DX_FATAL(...)	      ::Dunix::Log::GetClientLogger()->fatal(__VA_ARGS__)

namespace Dunix
{
	class DUNIX_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
