#pragma once

#include <Animation/Easing.hpp>
#include <Animation/Exceptions.hpp>
#include <Collision/Trajectory.hpp>
#include <Graphics/Color.hpp>
#include <Time/TimeUtils.hpp>
#include <Transform/AABB.hpp>
#include <Transform/Rect.hpp>
#include <Transform/UnitVector.hpp>

namespace obe::animation
{
    template <class T>
    class TweenImpl
    {
    public:
        static T step(double progression, const T& from, const T& to)
        {
            return from;
        }
    };
    template <>
    class TweenImpl<graphics::Color>
    {
    public:
        static graphics::Color step(
            double progression, const graphics::Color& from, const graphics::Color& to)
        {
            graphics::Color step = from;
            step.r = (progression * (to.r - from.r)) + from.r;
            step.g = (progression * (to.g - from.g)) + from.g;
            step.b = (progression * (to.b - from.b)) + from.b;
            step.a = (progression * (to.a - from.a)) + from.a;
            return step;
        }
    };
    template <>
    class TweenImpl<transform::UnitVector>
    {
    public:
        static transform::UnitVector step(
            double progression, const transform::UnitVector& from, const transform::UnitVector& to)
        {
            transform::UnitVector step = from;
            step.x = (progression * (to.x - from.x)) + from.x;
            step.y = (progression * (to.y - from.y)) + from.y;
            return step;
        }
    };
    template <>
    class TweenImpl<transform::AABB>
    {
    public:
        static transform::AABB step(
            double progression, const transform::AABB& from, const transform::AABB& to)
        {
            transform::AABB step = from;
            step.m_position = TweenImpl<transform::UnitVector>::step(progression, from.get_position(), to.get_position());
            step.m_size = TweenImpl<transform::UnitVector>::step(progression, from.get_size(), to.get_size());
            return step;
        }
    };
    template <>
    class TweenImpl<transform::Rect>
    {
    public:
        static transform::Rect step(
            double progression, const transform::Rect& from, const transform::Rect& to)
        {
            transform::Rect step = from;
            step.m_position = TweenImpl<transform::UnitVector>::step(
                progression, from.get_position(), to.get_position());
            step.m_size = TweenImpl<transform::UnitVector>::step(
                progression, from.get_size(), to.get_size());
            step.m_angle = (progression * (to.m_angle - from.m_angle)) + from.m_angle;
            return step;
        }
    };
    template <>
    class TweenImpl<collision::Trajectory>
    {
    public:
        static collision::Trajectory step(
            double progression, const collision::Trajectory& from, const collision::Trajectory& to)
        {
            collision::Trajectory step = from;
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
        static double step(double progression, const double& from, const double& to)
        {
            return (progression * (to - from)) + from;
        }
    };

    template <class T, std::size_t = sizeof(T)>
    std::true_type template_specialization_exists_impl(T*);

    /**
     * \nobind
     */
    std::false_type template_specialization_exists_impl(...);

    /**
     * \nobind
     */
    template <class T>
    using template_specialization_exists
        = decltype(template_specialization_exists_impl(std::declval<T*>()));

    /**
     * \thints
     * \thint{ColorTweening     , TweenableClass=obe::graphics::Color}
     * \thint{UnitVectorTweening, TweenableClass=obe::transform::UnitVector}
     * \thint{RectTweening      , TweenableClass=obe::transform::Rect}
     * \thint{TrajectoryTweening, TweenableClass=obe::collision::Trajectory}
     * \thint{IntTweening       , TweenableClass=int}
     * \thint{DoubleTweening    , TweenableClass=double}
     * \endthints
     *
     */
    template <class TweenableClass>
    class ValueTweening
    {
    private:
        easing::EasingFunction m_easing = easing::linear;
        TweenableClass m_from;
        TweenableClass m_to;
        double m_duration;
        double m_current = 0;
        bool m_started = false;

    public:
        explicit ValueTweening(
            time::TimeUnit duration, easing::EasingFunction easing = easing::linear)
            : m_easing(std::move(easing))
            , m_duration(duration)

        {
            static_assert(template_specialization_exists<TweenImpl<TweenableClass>>());
            if (!m_easing)
            {
                throw exceptions::InvalidEasingFunction(EXC_INFO);
            }
        }

        /**
         * \mergetemplatespecialisations{Tween}
         */
        ValueTweening(TweenableClass from, TweenableClass to, time::TimeUnit duration,
            easing::EasingFunction easing = easing::linear)
            : m_easing(std::move(easing))
            , m_from(from)
            , m_to(to)
            , m_duration(duration)
        {
            static_assert(template_specialization_exists<TweenImpl<TweenableClass>>());
            if (!m_easing)
            {
                throw exceptions::InvalidEasingFunction(EXC_INFO);
            }
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

        ValueTweening& ease(const easing::EasingFunction& easing)
        {
            m_easing = easing;
            return *this;
        }

        void start()
        {
            m_current = 0;
            m_started = true;
        }

        void stop()
        {
            m_started = false;
        }

        void seek(double progression)
        {
            m_current = m_duration * progression;
        }

        void reset()
        {
            m_current = 0;
        }

        void resume()
        {
            m_started = true;
        }

        [[nodiscard]] bool done() const
        {
            return (m_current / m_duration) >= 1;
        }

        TweenableClass step(const double dt)
        {
            if (!m_started)
            {
                return m_from;
            }
            m_current += dt;
            const double progression = m_current / m_duration;
            return TweenImpl<TweenableClass>::step(m_easing(progression), m_from, m_to);
        }
    };
} // namespace obe::animation
