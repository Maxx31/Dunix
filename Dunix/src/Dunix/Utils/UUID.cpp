#include "UUID.h"

#include <limits>
#include <random>

namespace
{
    thread_local std::mt19937_64 RandomEngine{
        std::random_device{}()
    };

    thread_local std::uniform_int_distribution<uint64_t> Distribution{
        1,
        std::numeric_limits<uint64_t>::max()
    };
}

namespace Dunix
{
    UUID::UUID()
        : m_Value(Distribution(RandomEngine))
    {
    }

    UUID::UUID(uint64_t value)
        : m_Value(value)
    {
    }
}