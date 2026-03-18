#include "dxpch.h"
#include "Profiler.h"

#include <fstream>

namespace Dunix
{
    Profiler* Profiler::Instance = nullptr;

    Profiler* Profiler::Get()
    {
        if (Instance == nullptr)
        {
            Instance = new Profiler();
        }

        return Instance;
    }
    
    void Profiler::PushEvent(std::string Name, uint64_t Start, uint64_t Duration)
    {
        Events.push_back({ Name, Start, Duration});
    }

    void Profiler::ExportToJson()
    {
        std::ofstream file("ProfileData");

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
