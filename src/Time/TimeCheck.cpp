#include <Time/TimeCheck.hpp>

namespace obe
{
    namespace Time
    {
        TimeCheck::TimeCheck(TimeUnit delay, bool initializeClock)
        {
            m_waitFor = delay;
            if (initializeClock)
            {
                m_clock = Time::getTickSinceEpoch();
            }
        }

        void TimeCheck::setDelay(TimeUnit delay)
        {
            m_waitFor = delay;
        }

        Time::TimeUnit TimeCheck::getDelay() const
        {
            return m_waitFor;
        }

        void TimeCheck::reset()
        {
            m_clock = Time::getTickSinceEpoch();
        }

        bool TimeCheck::over() const
        {
            return (m_waitFor == 0 || Time::getTickSinceEpoch() - m_clock >= m_waitFor);
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
    }
}