#pragma once

#include <functional>

#include <Time/TimeUtils.hpp>

namespace obe::event
{
    using Callback = std::function<void()>;
    class EventManager;

    enum class CallbackSchedulerState
    {
        Standby,
        Ready,
        Done
    };

    class CallbackScheduler
    {
    private:
        Callback m_callback;
        time::TimeUnit m_after = 0;
        time::TimeUnit m_every = 0;
        time::TimeUnit m_start = 0;
        unsigned int m_times = 0;
        unsigned int m_current_times = 0;
        bool m_wait = false;
        bool m_repeat = false;
        CallbackSchedulerState m_state = CallbackSchedulerState::Standby;
        void execute();

        friend class EventManager;

    public:
        explicit CallbackScheduler() = default;
        CallbackScheduler& after(double amount);
        CallbackScheduler& every(double amount);
        /**
         * \brief calls the callback `amount` times at the rate configured in the `every(x)` call
         *
         * \rename{replay}
         */
        CallbackScheduler& repeat(unsigned int amount);
        void run(const Callback& callback);
        void stop();
    };
}
