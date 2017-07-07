#include <chrono>

#include <Time/TimeUtils.hpp>

namespace obe
{
    namespace Time
    {
        TimeUnit getTickSinceEpoch()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        }

        TimeUnit getTickSinceEpochMicro()
        {
            return std::chrono::system_clock::now().time_since_epoch() / std::chrono::microseconds(1);
        }
    }
}