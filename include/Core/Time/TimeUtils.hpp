#pragma once

namespace obe::Time
{
    /**
     * \brief A time unit to store time as seconds
     */
    using TimeUnit = double;

    constexpr TimeUnit seconds = 1.0;
    constexpr TimeUnit milliseconds = seconds / 1000.0;
    constexpr TimeUnit microseconds = milliseconds / 1000.0;
    constexpr TimeUnit minutes = seconds * 60.0;
    constexpr TimeUnit hours = minutes * 60.0;
    constexpr TimeUnit days = hours * 24.0;
    constexpr TimeUnit weeks = days * 7.0;

    /**
     * \brief Get the amount of seconds elapsed since epoch
     * \return A TimeUnit containing the amount of seconds elapsed since
     *         Epoch
     */
    TimeUnit epoch();
} // namespace obe::Time