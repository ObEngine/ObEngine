#pragma once

#include <Animation/Easing.hpp>
#include <Time/TimeUtils.hpp>
#include <Types/Tweenable.hpp>

namespace obe::Animation
{
    /**
         * \thints
         * \thint{TestClass, T=obe::Types::Tweenable}
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
                std::is_same_v<double, TweenableClass> ||
                std::is_base_of_v<Types::Tweenable<1>, TweenableClass> ||
                std::is_base_of_v<Types::Tweenable<2>, TweenableClass> ||
                std::is_base_of_v<Types::Tweenable<3>, TweenableClass> ||
                std::is_base_of_v<Types::Tweenable<4>, TweenableClass>
                );
        }

        ValueTweening(TweenableClass from, TweenableClass to, Time::TimeUnit duration)
            : m_duration(duration)
            , m_from(from)
            , m_to(to)
        {
            static_assert(
                std::is_same_v<double, TweenableClass> ||
                std::is_base_of_v<Types::Tweenable<1>, TweenableClass> ||
                std::is_base_of_v<Types::Tweenable<2>, TweenableClass> ||
                std::is_base_of_v<Types::Tweenable<3>, TweenableClass> ||
                std::is_base_of_v<Types::Tweenable<4>, TweenableClass>
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

        template <class T = TweenableClass>
        std::enable_if_t<std::is_base_of_v<Types::Tweenable<2>, T>
                || std::is_base_of_v<Types::Tweenable<3>, T>
                || std::is_base_of_v<Types::Tweenable<4>, T>,
            T>
        step(double dt)
        {
            m_current += dt;
            const double progression = m_current / m_duration;
            TweenableClass step = m_from;
            auto componentsFrom = m_from.getNumericalComponents();
            auto componentsTo = m_to.getNumericalComponents();
            for (size_t i = 0; i < componentsFrom.size(); i++)
            {
                const double valueFrom = componentsFrom.at(i);
                const double valueTo = componentsTo.at(i);
                componentsFrom.at(i) = (m_easing(progression) * (valueTo - valueFrom)) + valueFrom;
            }
            step.setNumericalComponents(componentsFrom);
            return step;
        }

        template <class T = TweenableClass>
        std::enable_if_t<std::is_same_v<double, T>, T>
        step(double dt)
        {
            m_current += dt;
            const double progression = m_current / m_duration;
            return (m_easing(progression) * (m_to - m_from)) + m_from;
        }
    };
}
