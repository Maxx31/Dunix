#pragma once

using namespace std::chrono;

namespace Dunix
{
    class ProfileScope
    {
    public:
        ProfileScope(std::string name);
        ~ProfileScope();

    private:
        std::string m_name;
        time_point<steady_clock> m_startTime;
    };
}
