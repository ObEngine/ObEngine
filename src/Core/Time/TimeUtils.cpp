#include <chrono>

#include <Time/TimeUtils.hpp>

namespace obe::Time
{
    TimeUnit epoch()
    {
        return double(std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::system_clock::now().time_since_epoch())
                          .count())
            * microseconds;
    }
} // namespace obe::Time