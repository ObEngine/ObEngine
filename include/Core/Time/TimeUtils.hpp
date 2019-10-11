#pragma once

namespace obe::Time
{
    /**
     * \brief TimeUnit to store Epoch milli/micro seconds
     */
    using TimeUnit = unsigned long long; // <REVISION> Change this
    /**
     * \brief Get the amount of milliseconds elapsed since Epoch
     * \return A TimeUnit containing the amount of milliseconds elapsed since
     * Epoch
     */
    TimeUnit getTickSinceEpoch();
    /**
     * \brief Get the amount of microseconds elapsed since Epoch
     * \return A TimeUnit containing the amount of microseconds elapsed since
     * Epoch
     */
    TimeUnit getTickSinceEpochMicro();
} // namespace obe::Time