#pragma once

#include <string>
#include <chrono>

namespace Dunix
{
    class ProfileScope
    {
    public:
        ProfileScope(const std::string& name);
        ~ProfileScope();

    private:
        std::string m_name;
        std::chrono::time_point<std::chrono::steady_clock> m_startTime;
    };
}