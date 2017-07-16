#include <Triggers/TriggerDelay.hpp>

namespace obe
{
    namespace Triggers
    {
        TriggerDelay::TriggerDelay(Trigger* trg, unsigned int delay, bool state)
        {
            m_trigger = trg;
            m_delay = delay;
            m_state = state;
        }
    }
}