#pragma once

#include <Triggers/Trigger.hpp>

namespace obe
{
    namespace Triggers
    {
        class TriggerDelay
        {
        public:
            TriggerDelay(Trigger* trg, int del, bool sta);
            Trigger* m_trigger;
            int m_delay = 0;
            bool m_state = false;
            int m_delaytarget = 0;
        };
    }
}