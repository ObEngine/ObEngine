#pragma once

#include <Time/TimeUtils.hpp>

namespace obe::Time
{
    /**
     * \brief Class used to check if a certain time has been elapsed with a
     * delay
     */
    class TimeCheck
    {
    private:
        TimeUnit m_waitFor;
        TimeUnit m_clock;

    public:
        /**
         * \brief Constructor of TimeCheck
         * \param delay Delay of the TimeCheck in milliseconds
         * \param initializeClock Initialize the clock on construction
         */
        TimeCheck(TimeUnit delay, bool initializeClock = false);
        /**
         * \brief Sets the delay of the TimeCheck in milliseconds
         * \param delay Delay of the TimeCheck in milliseconds
         */
        void setDelay(TimeUnit delay);
        /**
         * \brief Gets the amount of milliseconds used by the TimeCheck
         * \return The amount of milliseconds used by the TimeCheck
         */
        TimeUnit getDelay() const;
        void reset();
        /**
         * \brief Checks if the TimeCheck is elapsed
         * \return true if the TimeCheck is elapsed, false otherwise
         */
        bool over() const;
        /**
         * \brief Resets the TimeCheck if elapsed
         * \return true if TimeCheck is elapsed, false otherwise
         */
        bool resetIfOver();
        /**
         * \brief Directly overs the TimeCheck so ::over() will return true
         */
        void goToOver();
    };
} // namespace obe::Time