#include <iostream>

#include <Time/Chronometer.hpp>

namespace obe::Time
{
    void Chronometer::start()
    {
        m_start = std::chrono::high_resolution_clock::now();
        m_started = true;
    }

    void Chronometer::stop()
    {
        m_started = false;
    }

    void Chronometer::reset()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }

    TimeUnit Chronometer::getTime() const
    {
        if (m_started)
            return std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - m_start)
                .count();
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
        return (!m_started xor this->getTime() > m_limit);
    }
} // namespace obe::Time