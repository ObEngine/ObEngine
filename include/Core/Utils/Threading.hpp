#pragma once

#include <memory>
#include <functional>

namespace obe::utils::threading
{
	class Thread
	{
    private:
        std::unique_ptr<std::thread> m_thread;
        std::function<void(bool)> m_on_complete;
        bool m_completed = false;
        bool m_success = false;
    public:
        Thread(std::function<bool()> callable);
        void on_complete(std::function<void(bool)> on_complete_callable);
        [[nodiscard]] bool is_complete() const;
        [[nodiscard]] bool is_success() const;

        void join();
        void detach();
	};
}