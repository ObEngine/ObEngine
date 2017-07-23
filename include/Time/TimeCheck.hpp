#pragma once

#include <Time/TimeUtils.hpp>

namespace obe
{
    namespace Time
    {
        class TimeCheck
        {
        private:
            TimeUnit m_waitFor;
            TimeUnit m_clock;
        public:
            TimeCheck(TimeUnit delay, bool initializeClock = false);
            void setDelay(TimeUnit delay);
            Time::TimeUnit getDelay() const;
            void reset();
            bool over() const;
            bool resetIfOver();
        };
    }
}