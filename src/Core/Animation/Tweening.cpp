#include <Animation/Tweening.hpp>
#include <iostream>

namespace obe::Animation
{
    ValueTweening::ValueTweening(Time::TimeUnit duration)
        : m_duration(duration)
    {
    }

    ValueTweening::ValueTweening(double from, double to, Time::TimeUnit duration)
        : m_from(from)
        , m_to(to - from)
        , m_duration(duration)
    {
    }

    ValueTweening& ValueTweening::from(double from)
    {
        m_from = from;
        return *this;
    }

    ValueTweening& ValueTweening::to(double to)
    {
        m_to = to;
        return *this;
    }

    ValueTweening& ValueTweening::ease(const Easing::EasingFunction& easing)
    {
        m_easing = easing;
        return *this;
    }

    double ValueTweening::step(double dt)
    {
        m_current += dt;
        const double progression = m_current / m_duration;
        return (m_easing(progression) * m_to) + m_from;
    }
}
