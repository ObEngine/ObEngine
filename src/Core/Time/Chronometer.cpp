#include <Time/Chronometer.hpp>

namespace obe::time
{
    void Chronometer::start()
    {
        m_start = epoch();
        m_started = true;
    }

    void Chronometer::stop()
    {
        m_started = false;
    }

    void Chronometer::reset()
    {
        m_start = epoch();
    }

    TimeUnit Chronometer::get_elapsed_time() const
    {
        if (m_started)
            return epoch() - m_start;
        return 0;
    }

    void Chronometer::set_limit(const TimeUnit limit)
    {
        m_limit = limit;
    }

    TimeUnit Chronometer::get_limit() const
    {
        return m_limit;
    }

    bool Chronometer::is_over() const
    {
        return ((!m_started) xor (this->get_elapsed_time() > m_limit));
    }
} // namespace obe::time
