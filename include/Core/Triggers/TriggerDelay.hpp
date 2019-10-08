#pragma once

#include <Time/TimeUtils.hpp>
#include <Triggers/Trigger.hpp>

namespace obe::Triggers
{
    /**
     * \brief Class used to enable / disable a Trigger after a delay
     * @Bind
     */
    class TriggerDelay
    {
    public:
        /**
         * \brief Creates a new TriggerDelay
         * \param trigger Pointer to the Trigger to delay
         * \param delay Delay until the Trigger activation (in ms)
         */
        TriggerDelay(Trigger* trigger, Time::TimeUnit delay);
        /**
         * \brief Trigger to enable /disable after the delay
         */
        Trigger* m_trigger;
        /**
         * \brief Delay the Trigger should be enabled / disabled (in
         * milliseconds)
         */
        Time::TimeUnit m_delay = 0;
        /**
         * \brief Internal use only
         */
        Time::TimeUnit m_delaytarget = 0;
    };
} // namespace obe::Triggers