#pragma once

#include <cstdint>
#include <functional>

namespace Dunix
{
    class UUID
    {
    public:
        UUID();
        
        // Creates a UUID from an existing value, usually during scene loading.
        explicit UUID(uint64_t value);

        // Returns the stored integer.
        [[nodiscard]] uint64_t Value() const
        {
            return m_Value;
        }

        // Allows explicit conversion: uint64_t value = static_cast<uint64_t>(id);
        explicit operator uint64_t() const
        {
            return m_Value;
        }

        bool operator==(const UUID& other) const
        {
            return m_Value == other.m_Value;
        }

        bool operator!=(const UUID& other) const
        {
            return !(*this == other);
        }

    private:
        uint64_t m_Value = 0;
    };
}

namespace std
{
    template<>
    struct hash<Dunix::UUID>
    {
        size_t operator()(const Dunix::UUID& uuid) const noexcept
        {
            return hash<uint64_t>{}(uuid.Value());
        }
    };
}