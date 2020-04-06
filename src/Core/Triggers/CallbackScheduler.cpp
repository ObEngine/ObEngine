#include <Triggers/CallbackScheduler.hpp>

namespace obe::Triggers
{
    void CallbackScheduler::execute()
    {
        if (!m_repeat)
        {
            m_ready = false;
        }
        else
        {
            m_start = Time::epochAsMicroseconds();
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

    void CallbackScheduler::run(const Callback& callback)
    {
        m_callback = callback;
        m_ready = true;
        m_start = Time::epochAsMicroseconds();
    }

    void CallbackScheduler::stop()
    {
        m_ready = false;
    }
}
