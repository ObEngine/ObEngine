#pragma once

#include <Event/CallbackScheduler.hpp>
#include <Event/Event.hpp>
#include <Event/EventGroup.hpp>
#include <Event/EventNamespace.hpp>
#include <Time/Chronometer.hpp>
#include <map>

namespace obe::event
{
    /**
     * \brief A EventManager that handles EventNamespaces and Schedulers
     */
    class EventManager
    {
    private:
        std::unordered_map<std::string, std::unique_ptr<EventNamespace>> m_namespaces;
        std::vector<std::unique_ptr<CallbackScheduler>> m_schedulers;
        time::Chronometer m_chrono;

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
        EventNamespace& create_namespace(const std::string& event_namespace);
        EventNamespace& join_namespace(const std::string& event_namespace);
        EventNamespaceView get_namespace(const std::string& event_namespace);

        [[nodiscard]] std::vector<std::string> get_all_namespaces_names() const;

        CallbackScheduler& schedule();
    };
} // namespace obe::event
