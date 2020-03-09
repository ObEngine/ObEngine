#include <iostream>

#include <Time/Chronometer.hpp>

namespace obe::Time
{
    void Chronometer::start()
    {
        m_start = std::chrono::high_resolution_clock::now();
        m_current = std::chrono::high_resolution_clock::now();
        m_started = true;
    }

    void Chronometer::stop()
    {
        m_started = false;
    }

    TimeUnit Chronometer::getTime()
    {
        if (m_started)
            m_current = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(m_current - m_start)
            .count();
    }

    void Chronometer::setLimit(const TimeUnit limit)
    {
        m_limit = limit;
    }

    bool Chronometer::limitExceeded()
    {
        return (m_started && this->getTime() > m_limit);
    }
} // namespace obe::Time