#include "dxpch.h"
#include "Time.h"

namespace Dunix
{
	const float Time::GetTime()
	{
		using clock = std::chrono::steady_clock;
		static auto start = clock::now();
		return std::chrono::duration<float>(clock::now() - start).count();
	}
}
