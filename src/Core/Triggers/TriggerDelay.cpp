#include <Triggers/TriggerDelay.hpp>

namespace obe::Triggers
{
    TriggerDelay::TriggerDelay(Trigger* trigger, Time::TimeUnit delay)
    {
        m_trigger = trigger;
        m_delay = delay;
    }
} // namespace obe::Triggers