#include <Utils/Threading.hpp>

namespace obe::utils::threading
{
    Thread::Thread(std::function<bool()> callable)
    {
        m_thread = std::make_unique<std::thread>([callable, this]() {
            try
            {
                m_success = callable();
            }
            catch (const std::exception& exc)
            {
                m_success = false;
            }
            m_completed = true;
            if (m_on_complete)
            {
                m_on_complete(m_success);
            }
        });
    }

    void Thread::on_complete(std::function<void(bool)> on_complete_callable)
    {
        m_on_complete = on_complete_callable;
        if (m_completed)
        {
            m_on_complete(m_success);
        }
    }

    bool Thread::is_complete() const
    {
        return m_completed;
    }

    bool Thread::is_success() const
    {
        return m_success;
    }

    void Thread::join()
    {
        m_thread->join();
    }

    void Thread::detach()
    {
        m_thread->detach();
    }
}