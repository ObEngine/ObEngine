#include <Triggers/CallbackScheduler.hpp>

namespace obe::Triggers
{
    void CallbackScheduler::execute()
    {
        if (!m_repeat)
        {
            m_state = CallbackSchedulerState::Done;
        }
        else
        {
            if (m_times > 0 && m_times == (m_currentTimes - 1))
            {
                m_state = CallbackSchedulerState::Done;
            }
            else
            {
                m_start = Time::epoch();
                m_currentTimes++;
            }
        }
        m_callback();
    }

    CallbackScheduler::CallbackScheduler(TriggerManager& manager)
        : m_triggers(manager)
    {
    }

    CallbackScheduler& CallbackScheduler::after(double amount)
    {
        m_after = amount;
        m_wait = true;
        return *this;
    }

    CallbackScheduler& CallbackScheduler::every(double amount)
    {
        m_every = amount;
        m_repeat = true;
        return *this;
    }

    CallbackScheduler& CallbackScheduler::repeat(unsigned amount)
    {
        m_times = amount;
        return *this;
    }

    void CallbackScheduler::run(const Callback& callback)
    {
        m_callback = callback;
        m_state = CallbackSchedulerState::Ready;
        m_start = Time::epoch();
    }

    void CallbackScheduler::stop()
    {
        m_state = CallbackSchedulerState::Done;
    }
}
