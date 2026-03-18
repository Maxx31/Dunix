#pragma once
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
    
        static Profiler* Get();
    
        void PushEvent(std::string Name, uint64_t Start, uint64_t Duration);
        void ExportToJson();
        
        static Profiler* Instance;
        
    private:
        std::vector<ProfileEvent> Events;
    };
    
}
