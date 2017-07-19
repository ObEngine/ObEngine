#pragma once

#include <Triggers/Trigger.hpp>
#include "Time/TimeUtils.hpp"

namespace obe
{
    namespace Triggers
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
             * \param state 
             */
            TriggerDelay(Trigger* trigger, Time::TimeUnit delay, bool state);
            /**
             * \brief Trigger to enable /disable after the delay
             */
            Trigger* m_trigger;
            /**
             * \brief Delay the Trigger should be enabled / disabled (in milliseconds)
             */
            Time::TimeUnit m_delay = 0;
            /**
             * \brief State to set to the Trigger
             */
            bool m_state = false;
            /**
             * \brief Internal use only
             */
            Time::TimeUnit m_delaytarget = 0;
        };
    }
}
