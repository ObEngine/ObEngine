#include <Event/CallbackScheduler.hpp>

namespace obe::event
{
    void CallbackScheduler::execute()
    {
        if (!m_repeat)
        {
            m_state = CallbackSchedulerState::Done;
        }
        else
        {
            if (m_times > 0 && m_times == (m_current_times - 1))
            {
                m_state = CallbackSchedulerState::Done;
            }
            else
            {
                m_start = time::epoch();
                m_current_times++;
            }
        }
        m_callback();
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

    CallbackScheduler& CallbackScheduler::repeat(unsigned int amount)
    {
        m_times = amount;
        return *this;
    }

    void CallbackScheduler::run(const Callback& callback)
    {
        m_callback = callback;
        m_state = CallbackSchedulerState::Ready;
        m_start = time::epoch();
    }

    void CallbackScheduler::stop()
    {
        m_state = CallbackSchedulerState::Done;
    }
}
