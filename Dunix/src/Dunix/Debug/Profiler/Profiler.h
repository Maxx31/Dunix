#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace Dunix
{
    struct ProfileEvent
    {
        std::string Name;
        uint64_t Start;
        uint64_t Duration;
        uint32_t ThreadId;
    };

    class Profiler
    {
    public:
        static Profiler& Get();

        void BeginSession();
        void EndSession();
        void PushEvent(const std::string& Name, uint64_t Start, uint64_t Duration);
        void ExportToJson(const std::string& filePath = "ProfileData.json");

    private:
        std::vector<ProfileEvent> Events;
        uint64_t m_sessionStartUs = 0;
        bool m_sessionActive = false;
    };
}