#pragma once

namespace obe
{
    namespace Time
    {
        /**
        * \brief TimeUnit to store Epoch milli/micro seconds
        */
        typedef unsigned long long int TimeUnit;
        /**
        * \brief Get the amount of milliseconds elapsed since Epoch
        * \return A TimeUnit containing the amount of milliseconds elapsed since Epoch
        */
        TimeUnit getTickSinceEpoch();
        /**
        * \brief Get the amount of microseconds elapsed since Epoch
        * \return A TimeUnit containing the amount of microseconds elapsed since Epoch
        */
        TimeUnit getTickSinceEpochMicro();
    }
}
