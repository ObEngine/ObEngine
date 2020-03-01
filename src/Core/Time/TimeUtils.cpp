#include <chrono>

#include <Time/TimeUtils.hpp>

namespace obe::Time
{
    TimeUnit epochAsMilliseconds()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
    }

    TimeUnit epochAsMicroseconds()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
    }
} // namespace obe::Time