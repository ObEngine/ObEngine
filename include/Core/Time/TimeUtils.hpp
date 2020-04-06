#pragma once

namespace obe::Time
{
    /**
     * \brief TimeUnit to store Epoch milli/micro seconds
     */
    using TimeUnit = unsigned long long; // <REVISION> Change this

    constexpr TimeUnit microseconds = 1;
    constexpr TimeUnit milliseconds = microseconds * 1000;
    constexpr TimeUnit seconds = milliseconds * 1000;
    constexpr TimeUnit minutes = seconds * 60;
    constexpr TimeUnit hours = minutes * 60;
    constexpr TimeUnit days = hours * 24;
    constexpr TimeUnit weeks = days * 7;

    /**
     * \brief Get the amount of milliseconds elapsed since Epoch
     * \return A TimeUnit containing the amount of milliseconds elapsed since
     *         Epoch
     */
    TimeUnit epochAsMilliseconds();
    /**
     * \brief Get the amount of microseconds elapsed since Epoch
     * \return A TimeUnit containing the amount of microseconds elapsed since
     *         Epoch
     */
    TimeUnit epochAsMicroseconds();
} // namespace obe::Time