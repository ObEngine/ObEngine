#pragma once

#include <map>

#include <Event/CallbackScheduler.hpp>
#include <Event/Event.hpp>
#include <Event/EventGroup.hpp>
#include <Time/Chronometer.hpp>

namespace obe::Event
{
    /**
     * \brief A EventManager that handles all Trigger / TriggerGroup
     */
    class EventManager
    {
    private:
        std::map<std::string, std::map<std::string, std::weak_ptr<EventGroup>>> m_groups;
        std::vector<std::unique_ptr<CallbackScheduler>> m_schedulers;
        Time::Chronometer m_chrono;
        sol::state_view m_lua;

    public:
        explicit EventManager();
        /**
         * \brief Get a Trigger contained in the EventManager
         * \param space Namespace of the Trigger
         * \param group TriggerGroup of the Trigger
         * \param trigger Name of the Trigger
         * \return A pointer of the Trigger if found
         */
        std::weak_ptr<Event> getEvent(const std::string& space, const std::string& group,
            const std::string& trigger);
        /**
         * \brief Get a list of all names of Trigger instances inside a TriggerGroup
         * \param eventNamespace Name of the namespace where the TriggerGroup is located
         * \param eventGroup Name of the TriggerGroup you want the names of the Trigger
         *        instances from
         * \return A list of names of the Triggers inside the TriggerGroup
         */
        std::vector<std::string> getEventsNames(
            const std::string& eventNamespace, const std::string& eventGroup);
        /**
         * \brief Creates a new namespace (Throws an error if the namespace
         *        already exists)
         * \param space Name of the namespace to create
         */
        void createNamespace(const std::string& space);
        /**
         * \brief Creates a new TriggerGroup (Throws an error if the
         *        TriggerGroup already exists)
         * \param space Namespace where to
         *        create the TriggerGroup
         * \param group Name of the new TriggerGroup
         * \return Pointer to the newly created TriggerGroup
         */
        EventGroupPtr createEventGroup(
            const std::string& eventNamespace, const std::string& eventGroup);
        /**
         * \brief Join an existing TriggerGroup (Throws an error if the
         *        TriggerGroup does not exists or isn't joinable)
         * \param space Namespace of the existing TriggerGroup
         * \param group Name of the TriggerGroup to join
         * \return Pointer to the newly joined TriggerGroup
         */
        EventGroupPtr joinEventGroup(
            const std::string& eventNamespace, const std::string& eventGroup);
        /**
         * \brief Get all the names of the TriggerGroup in the given Namespace
         * \param space Namespace where to get all the TriggerGroup
         *        names
         * \return A std::vector of std::string containing the names of
         *         all contained TriggerGroup
         */
        std::vector<std::string> getAllEventGroupsNames(
            const std::string& eventNamespace);
        /**
         * \brief Removes an existing namespace
         * \param space Name of the namespace to delete
         */
        void removeNamespace(const std::string& eventNamespace);
        /**
         * \brief Removes an existing TriggerGroup
         * \param group Pointer to the TriggerGroup to delete
         */
        void removeTriggerGroup(TriggerGroup* group);
        /**
         * \brief Check if a TriggerGroup exists in the EventManager
         * \param space Name of the Namespace where to search if the
         *        TriggerGroup exists
         * \param group Name of the TriggerGroup
         *        to search
         * \return true if the TriggerGroup exists, false otherwise
         */
        bool doesTriggerGroupExists(const std::string& space, const std::string& group);
        /**
         * \brief Updates the EventManager
         */
        void update();
        /**
         * \brief Clears the EventManager
         */
        void clear();

        CallbackScheduler& schedule();
        vili::node dumpProfilerResults();
    };
} // namespace obe::Triggers
