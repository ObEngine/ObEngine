#pragma once

#include <functional>

#include <Time/TimeUtils.hpp>

namespace obe::Triggers
{
    using Callback = std::function<void()>;
    class TriggerManager;

    class CallbackScheduler
    {
    private:
        Callback m_callback;
        TriggerManager& m_triggers;
        Time::TimeUnit m_after = 0;
        Time::TimeUnit m_every = 0;
        Time::TimeUnit m_start = 0;
        bool m_wait = false;
        bool m_repeat = false;
        bool m_ready = false;
        void execute();

        friend class TriggerManager;

    public:
        explicit CallbackScheduler(TriggerManager& manager);
        CallbackScheduler& after(double amount);
        CallbackScheduler& every(double amount);
        void run(const Callback& callback);
        void stop();
    };
}
