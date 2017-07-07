#include <Triggers/TriggerDelay.hpp>

namespace obe
{
    namespace Triggers
    {
        TriggerDelay::TriggerDelay(Trigger* trg, int del, bool sta)
        {
            m_trigger = trg;
            m_delay = del;
            m_state = sta;
        }
    }
}