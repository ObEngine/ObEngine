#pragma once

#include <map>

#include <Event/CallbackScheduler.hpp>
#include <Event/Event.hpp>
#include <Event/EventGroup.hpp>
#include <Event/EventNamespace.hpp>
#include <Time/Chronometer.hpp>

namespace obe::Event
{
    /**
     * \brief A EventManager that handles EventNamespaces and Schedulers
     */
    class EventManager
    {
    private:
        std::unordered_map<std::string, std::unique_ptr<EventNamespace>> m_namespaces;
        std::vector<std::unique_ptr<CallbackScheduler>> m_schedulers;
        Time::Chronometer m_chrono;

    public:
        explicit EventManager();
        /**
         * \brief Updates the EventManager
         */
        void update();
        /**
         * \brief Clears the EventManager
         */
        void clear();
        /*
         * \brief Gets the root EventGroup
         */
        EventNamespace& createNamespace(const std::string& eventNamespace);

        CallbackScheduler& schedule();
        vili::node dumpProfilerResults() const;
    };
} // namespace obe::Event
