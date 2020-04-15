#pragma once

#include <functional>

#include <Time/TimeUtils.hpp>

namespace obe::Triggers
{
    using Callback = std::function<void()>;
    class TriggerManager;

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
        TriggerManager& m_triggers;
        Time::TimeUnit m_after = 0;
        Time::TimeUnit m_every = 0;
        Time::TimeUnit m_start = 0;
        unsigned int m_times = 0;
        unsigned int m_currentTimes = 0;
        bool m_wait = false;
        bool m_repeat = false;
        CallbackSchedulerState m_state = CallbackSchedulerState::Standby;
        void execute();

        friend class TriggerManager;

    public:
        explicit CallbackScheduler(TriggerManager& manager);
        CallbackScheduler& after(double amount);
        CallbackScheduler& every(double amount);
        CallbackScheduler& repeat(unsigned int amount);
        void run(const Callback& callback);
        void stop();
    };
}
