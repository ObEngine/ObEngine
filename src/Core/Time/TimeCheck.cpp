#include <Time/TimeCheck.hpp>

namespace obe::Time
{
    TimeCheck::TimeCheck(const TimeUnit delay, const bool initializeClock)
    {
        m_waitFor = delay;
        if (initializeClock)
        {
            m_clock = epochAsMilliseconds();
        }
    }

    void TimeCheck::setDelay(const TimeUnit delay)
    {
        m_waitFor = delay;
    }

    Time::TimeUnit TimeCheck::getDelay() const
    {
        return m_waitFor;
    }

    void TimeCheck::reset()
    {
        m_clock = epochAsMilliseconds();
    }

    bool TimeCheck::over() const
    {
        return (m_waitFor == 0 || epochAsMilliseconds() - m_clock >= m_waitFor);
    }

    bool TimeCheck::resetIfOver()
    {
        if (this->over())
        {
            this->reset();
            return true;
        }
        else
        {
            return false;
        }
    }

    void TimeCheck::goToOver()
    {
        if (m_waitFor != 0)
        {
            m_clock = epochAsMilliseconds() - m_waitFor;
        }
    }
} // namespace obe::Time