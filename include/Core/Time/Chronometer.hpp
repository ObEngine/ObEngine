#pragma once

#include <Time/TimeUtils.hpp>

namespace obe::time
{
    /**
     * \brief A Chronometer class to measure time
     */
    class Chronometer
    {
    private:
        TimeUnit m_start = 0;
        TimeUnit m_limit = 0;
        bool m_started = false;

    public:
        /**
         * \brief Starts the Chronometer
         */
        void start();
        /**
         * \brief Stops the Chronometer
         */
        void stop();
        /**
         * \brief Resets the Chronometer
         */
        void reset();
        /**
         * \brief Get Time elapsed since the Chronometer started
         * \return The amount of milliseconds elapsed since the Chronometer
         * started
         */
        [[nodiscard]] TimeUnit get_elapsed_time() const;
        /**
         * \brief Defines a limit to the Chronometer
         * \param limit The amount of milliseconds before the limit is exceeded
         */
        void set_limit(TimeUnit limit);
        [[nodiscard]] TimeUnit get_limit() const;
        /**
         * \brief Check if the defined limit has been exceeded
         * \return true if the limit has been exceeded, false otherwise.
         */
        [[nodiscard]] bool is_over() const;
    };
} // namespace obe::time
