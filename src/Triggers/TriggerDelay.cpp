#include <Triggers/TriggerDelay.hpp>

namespace obe
{
    namespace Triggers
    {
        TriggerDelay::TriggerDelay(Trigger* trigger, Time::TimeUnit delay, bool state)
        {
            m_trigger = trigger;
            m_delay = delay;
            m_state = state;
        }
    }
}