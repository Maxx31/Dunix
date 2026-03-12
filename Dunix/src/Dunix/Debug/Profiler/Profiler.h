#pragma once

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
    Profiler();
    ~Profiler();
    
    void PushEvent(std::string Name, uint64_t Start, uint64_t Duration, uint32_t ThreadId);
    void ExportToJson(ProfileEvent event);
};
