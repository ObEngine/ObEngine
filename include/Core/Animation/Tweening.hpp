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
    template <class TestClass>
    class ValueTweening
    {
    private:
        Easing::EasingFunction m_easing = Easing::Linear;
        TestClass m_from;
        TestClass m_to;
        double m_duration;
        double m_current = 0;

    public:
        ValueTweening(Time::TimeUnit duration)
            : m_duration(duration)
        {
        }

        ValueTweening(TestClass from, TestClass to, Time::TimeUnit duration)
            : m_from(from)
            , m_to(to)
            , m_duration(duration)
        {
        }

        ValueTweening& from(TestClass from)
        {
            m_from = from;
            return *this;
        }

        ValueTweening& to(TestClass to)
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
        
        template <class T = TestClass>
        typename std::enable_if<std::is_base_of<Types::Tweenable<2>, T>::value
                || std::is_base_of<Types::Tweenable<3>, T>::value
                || std::is_base_of<Types::Tweenable<4>, T>::value,
            TestClass>::type
        step(double dt)
        {
            m_current += dt;
            const double progression = m_current / m_duration;
            TestClass step = m_from;
            auto componentsFrom = m_from.getNumericalComponents();
            auto componentsTo = m_to.getNumericalComponents();
            for (size_t i = 0; i < componentsFrom.size(); i++)
            {
                double valueFrom = componentsFrom.at(i);
                double valueTo = componentsTo.at(i);
                componentsFrom.at(i) = (m_easing(progression) * (valueFrom - valueTo)) + valueFrom;
            }
            step.setNumericalComponents(componentsFrom);
            return step;
        }

        template <class T = TestClass>
            typename std::enable_if<!std::is_base_of<Types::Tweenable<2>, T>::value
                    && !std::is_base_of<Types::Tweenable<3>, T>::value
                    && !std::is_base_of<Types::Tweenable<4>, T>::value,
                TestClass>::type
        step(double dt)
        {
            m_current += dt;
            const double progression = m_current / m_duration;
            return (m_easing(progression) * (m_from - m_to)) + m_from;
        }
    };
}
