#pragma once

#include <Animation/Easing.hpp>
#include <Time/TimeUtils.hpp>
#include <Transform/UnitVector.hpp>
#include <Transform/Rect.hpp>
#include <Collision/Trajectory.hpp>
#include <Graphics/Color.hpp>

namespace obe::Animation
{
    template <class T>
    class TweenImpl
    {
    public:
        static T step(double progression, const T& from, const T& to) = 0;
    };
    template <>
    class TweenImpl<Graphics::Color>
    {
    public:
        static Graphics::Color step(double progression, const Graphics::Color& from, const Graphics::Color& to)
        {
            Graphics::Color step = from;
            step.r = (progression * (to.r - from.r)) + from.r;
            step.g = (progression * (to.g - from.g)) + from.g;
            step.b = (progression * (to.b - from.b)) + from.b;
            step.a = (progression * (to.a - from.a)) + from.a;
            return step;
        }
    };
    template <>
    class TweenImpl<Transform::UnitVector>
    {
    public:
        static Transform::UnitVector step(
            double progression, const Transform::UnitVector& from, const Transform::UnitVector& to)
        {
            Transform::UnitVector step = from;
            step.x = (progression * (to.x - from.x)) + from.x;
            step.y = (progression * (to.y - from.y)) + from.y;
            return step;
        }
    };
    template <>
    class TweenImpl<Transform::Rect>
    {
    public:
        static Transform::Rect step(
            double progression, const Transform::Rect& from, const Transform::Rect& to)
        {
            Transform::Rect step = from;
            step.m_size.x = (progression * (to.m_size.x - from.m_size.x)) + from.m_size.x;
            step.m_size.y = (progression * (to.m_size.y - from.m_size.y)) + from.m_size.y;
            step.m_angle = (progression * (to.m_angle - from.m_angle)) + from.m_angle;
            return step;
        }
    };
    template <>
    class TweenImpl<Collision::Trajectory>
    {
    public:
        static Collision::Trajectory step(
            double progression, const Collision::Trajectory& from, const Collision::Trajectory& to)
        {
            Collision::Trajectory step = from;
            step.m_acceleration
                = (progression * (to.m_acceleration - from.m_acceleration)) + from.m_acceleration;
            step.m_angle = (progression * (to.m_angle - from.m_angle)) + from.m_angle;
            step.m_speed = (progression * (to.m_speed - from.m_speed)) + from.m_speed;
            return step;
        }
    };
    template <>
    class TweenImpl<int>
    {
    public:
        static int step(int progression, const int& from, const int& to)
        {
            return (progression * (to - from)) + from;
        }
    };

    template <>
    class TweenImpl<double>
    {
    public:
        static double step(
            double progression, const double& from, const double& to)
        {
            return (progression * (to - from)) + from;
        }
    };

    template <class T, std::size_t = sizeof(T)>
    std::true_type template_specialization_exists_impl(T*);

    std::false_type template_specialization_exists_impl(...);

    template <class T>
    using template_specialization_exists
        = decltype(template_specialization_exists_impl(std::declval<T*>()));


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
        explicit ValueTweening(Time::TimeUnit duration)
            : m_duration(duration)
        {
            static_assert(template_specialization_exists<TweenImpl<TweenableClass>>());
        }

        ValueTweening(TweenableClass from, TweenableClass to, Time::TimeUnit duration)
            : m_duration(duration)
            , m_from(from)
            , m_to(to)
        {
            static_assert(template_specialization_exists<TweenImpl<TweenableClass>>());
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
            return TweenImpl<TweenableClass>::step(m_easing(progression), m_from, m_to);
        }
    };
}
