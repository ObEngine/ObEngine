#pragma once

#include <Triggers/Trigger.hpp>

namespace obe
{
    namespace Triggers
    {
        class TriggerDelay
        {
        public:
            TriggerDelay(Trigger* trg, unsigned int delay, bool state);
            Trigger* m_trigger;
            unsigned int m_delay = 0;
            bool m_state = false;
            int m_delaytarget = 0;
        };
    }
}