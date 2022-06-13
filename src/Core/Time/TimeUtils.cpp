#include <chrono>

#include <Time/TimeUtils.hpp>

namespace obe::time
{
    TimeUnit epoch()
    {
        return std::chrono::duration<double>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    }
} // namespace obe::time
