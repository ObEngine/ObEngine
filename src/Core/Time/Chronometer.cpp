#include <iostream>

#include <Time/Chronometer.hpp>

namespace obe::Time
{
    void Chronometer::start()
    {
        m_start = epoch();
        m_started = true;
    }

    bool Chronometer::started() const {
        if(m_started) 
            return true;
        return false;
    }
    void Chronometer::stop()
    {
        m_started = false;
    }

    void Chronometer::reset()
    {
        m_start = epoch();
    }

    TimeUnit Chronometer::getTime() const
    {
        if (m_started)
            return epoch() - m_start;
        return 0;
    }

    void Chronometer::setLimit(const TimeUnit limit)
    {
        m_limit = limit;
    }

    TimeUnit Chronometer::getLimit() const
    {
        return m_limit;
    }

    bool Chronometer::over() const
    {
        return ((!started()) xor (this->getTime() > m_limit));
    }
} // namespace obe::Time