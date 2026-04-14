#include "dxpch.h"
#include "Profiler.h"

#include <fstream>
#include <chrono>

namespace Dunix
{
    static uint64_t GetTimeMicroseconds()
    {
        using namespace std::chrono;
        return duration_cast<microseconds>(
            steady_clock::now().time_since_epoch()
        ).count();
    }

    Profiler& Profiler::Get()
    {
        static Profiler Instance;
        return Instance;
    }

    void Profiler::BeginSession()
    {
        Events.clear();
        m_sessionStartUs = GetTimeMicroseconds();
        m_sessionActive = true;
    }

    void Profiler::EndSession()
    {
        m_sessionActive = false;
    }

    void Profiler::PushEvent(const std::string& Name, uint64_t Start, uint64_t Duration)
    {
        if (!m_sessionActive)
            return;

        uint64_t RelativeStart = Start - m_sessionStartUs;
        Events.push_back({ Name, RelativeStart, Duration, 0 });
    }

    void Profiler::ExportToJson(const std::string& filePath)
    {
        std::ofstream file(filePath);

        file << "{\n";
        file << "\"traceEvents\": [\n";

        for (size_t i = 0; i < Events.size(); ++i)
        {
            const ProfileEvent& e = Events[i];

            file << "{";
            file << "\"name\":\"" << e.Name << "\",";
            file << "\"cat\":\"function\",";
            file << "\"ph\":\"X\",";
            file << "\"ts\":" << e.Start << ",";
            file << "\"dur\":" << e.Duration << ",";
            file << "\"pid\":1,";
            file << "\"tid\":" << e.ThreadId;
            file << "}";

            if (i + 1 < Events.size())
                file << ",";

            file << "\n";
        }

        file << "]\n";
        file << "}\n";
    }
}