#pragma once

#include <Animation/Easing.hpp>
#include <Time/TimeUtils.hpp>
#include <Transform/UnitVector.hpp>
#include <Transform/Rect.hpp>
#include <Collision/Trajectory.hpp>
#include <Graphics/Color.hpp>

namespace obe::Animation
{
    template<class T>
    class TweenImpl
    {
    public:
        static T step(double multiplier, const T& from, const T& to)
        {
            return T();
        }
    };
    template <>
    class TweenImpl<Graphics::Color>
    {
    public:
        static Graphics::Color step(double multiplier, const Graphics::Color& from, const Graphics::Color& to)
        {
            Graphics::Color step = from;
            step.r = (multiplier * (to.r - from.r)) + from.r;
            step.g = (multiplier * (to.g - from.g)) + from.g;
            step.b = (multiplier * (to.b - from.b)) + from.b;
            step.a = (multiplier * (to.a - from.a)) + from.a;
            return step;
        }
    };
    template <>
    class TweenImpl<Transform::UnitVector>
    {
    public:
        static Transform::UnitVector step(
            double multiplier, const Transform::UnitVector& from, const Transform::UnitVector& to)
        {
            Transform::UnitVector step = from;
            step.x = (multiplier * (to.x - from.x)) + from.x;
            step.y = (multiplier * (to.y - from.y)) + from.y;
            return step;
        }
    };
    template <>
    class TweenImpl<Transform::Rect>
    {
    public:
        static Transform::Rect step(
            double multiplier, const Transform::Rect& from, const Transform::Rect& to)
        {
            Transform::Rect step = from;
            step.m_size.x = (multiplier * (to.m_size.x - from.m_size.x)) + from.m_size.x;
            step.m_size.y = (multiplier * (to.m_size.y - from.m_size.y)) + from.m_size.y;
            step.m_angle = (multiplier * (to.m_angle - from.m_angle)) + from.m_angle;
            return step;
        }
    };
    template <>
    class TweenImpl<Collision::Trajectory>
    {
    public:
        static Collision::Trajectory step(
            double multiplier, const Collision::Trajectory& from, const Collision::Trajectory& to)
        {
            Collision::Trajectory step = from;
            step.m_acceleration
                = (multiplier * (to.m_acceleration - from.m_acceleration)) + from.m_acceleration;
            step.m_angle = (multiplier * (to.m_angle - from.m_angle)) + from.m_angle;
            step.m_speed = (multiplier * (to.m_speed - from.m_speed)) + from.m_speed;
            return step;
        }
    };
    template <>
    class TweenImpl<int>
    {
    public:
        static int step(int multiplier, const int& from, const int& to)
        {
            return (multiplier * (to - from)) + from;
        }
    };

    template <>
    class TweenImpl<double>
    {
    public:
        static double step(
            double multiplier, const double& from, const double& to)
        {
            return (multiplier * (to - from)) + from;
        }
    };
    /**
         * \thints
         * \thint{Color, T=obe::Graphics::Color}
         * \thint{UnitVector, T=obe::Transform::UnitVector}
         * \thint{Rect, T=obe::Transform::Rect}
         * \thint{Trajectory, T=obe::Collision::Trajectory}
         * \thint{Int, T=int}
         * \thint{Double, T=double}
         * \endthints
         *
         */
    template <class TweenableClass>
    class ValueTweening
    {
    private:
        Easing::EasingFunction m_easing = Easing::Linear;
        TweenableClass m_from;
        TweenableClass m_to;
        double m_duration;
        double m_current = 0;

    public:
        ValueTweening(Time::TimeUnit duration)
            : m_duration(duration)
        {
            static_assert(
                std::is_same_v<int, TweenableClass> || 
                std::is_same_v<double, TweenableClass> ||
                std::is_same_v<Graphics::Color, TweenableClass> ||
                std::is_same_v<Transform::UnitVector, TweenableClass> ||
                std::is_same_v<Transform::Rect, TweenableClass> || 
                std::is_same_v<Collision::Trajectory, TweenableClass>
                );
        }

        ValueTweening(TweenableClass from, TweenableClass to, Time::TimeUnit duration)
            : m_duration(duration)
            , m_from(from)
            , m_to(to)
        {
            static_assert(
                std::is_same_v<int, TweenableClass> ||
                std::is_same_v<double, TweenableClass> ||
                std::is_same_v<Graphics::Color, TweenableClass> ||
                std::is_same_v<Transform::UnitVector, TweenableClass> ||
                std::is_same_v<Transform::Rect, TweenableClass> ||
                std::is_same_v<Collision::Trajectory, TweenableClass>
                );
        }

        ValueTweening& from(TweenableClass from)
        {
            m_from = from;
            return *this;
        }

        ValueTweening& to(TweenableClass to)
        {
            m_to = to;
            return *this;
        }

        ValueTweening& ease(const Easing::EasingFunction& easing)
        {
            m_easing = easing;
            return *this;
        }

        bool done() const
        {
            return (m_current / m_duration) >= 1;
        }

        TweenableClass step(double dt)
        {
            m_current += dt;
            const double progression = m_current / m_duration;
            return TweenImpl<TweenableClass>::step(m_easing(progression), from, to);
        }
    };
}
