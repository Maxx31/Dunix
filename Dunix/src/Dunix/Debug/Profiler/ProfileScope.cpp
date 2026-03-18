#include "dxpch.h"
#include "ProfileScope.h"
#include "Profiler.h"

using namespace std::chrono;

namespace Dunix {

    ProfileScope::ProfileScope(std::string name)
    {
        m_startTime = high_resolution_clock::now();
    }

    ProfileScope::~ProfileScope()
    {
        auto Start = m_startTime.time_since_epoch().count();
        auto Duration = (high_resolution_clock::now() - m_startTime).count();
        auto Name = m_name;
        
        Profiler::Get()->PushEvent(Name, Start, Duration);
        Profiler::Get()->ExportToJson();
    }
}
