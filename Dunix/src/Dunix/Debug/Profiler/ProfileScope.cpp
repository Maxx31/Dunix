#include "dxpch.h"
#include "ProfileScope.h"
#include "Profiler.h"

namespace Dunix
{
    ProfileScope::ProfileScope(const std::string& name)
        : m_name(name), m_startTime(std::chrono::steady_clock::now())
    {
    }

    ProfileScope::~ProfileScope()
    {
        using namespace std::chrono;

        uint64_t Start = duration_cast<microseconds>(
            m_startTime.time_since_epoch()
        ).count();

        uint64_t Duration = duration_cast<microseconds>(
            steady_clock::now() - m_startTime
        ).count();

        Profiler::Get().PushEvent(m_name, Start, Duration);
    }
}