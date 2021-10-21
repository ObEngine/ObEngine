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
        EventNamespace& joinNamespace(const std::string& eventNamespace);
        EventNamespaceView getNamespace(const std::string& eventNamespace);

        std::vector<std::string> getAllNamespacesNames() const;

        CallbackScheduler& schedule();
        vili::node dumpProfilerResults() const;
    };

    inline std::vector<std::string> EventManager::getAllNamespacesNames() const
    {
        std::vector<std::string> allNames;
        allNames.reserve(m_namespaces.size());
        for (const auto& eventNamespace : m_namespaces)
        {
            allNames.push_back(eventNamespace.first);
        }
        return allNames;
    }
} // namespace obe::Event
