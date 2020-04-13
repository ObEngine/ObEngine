#pragma once

#include <Animation/Easing.hpp>
#include <Time/TimeUtils.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::Animation
{
    class ValueTweening
    {
    private:
        Easing::EasingFunction m_easing = Easing::Linear;
        double m_from;
        double m_to;
        double m_duration;
        double m_current = 0;

    public:
        ValueTweening(Time::TimeUnit duration);
        ValueTweening(double from, double to, Time::TimeUnit duration);
        ValueTweening& from(double from);
        ValueTweening& to(double to);
        ValueTweening& ease(const Easing::EasingFunction& easing);
        double step(double dt);
    };
}