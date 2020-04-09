#pragma once

#include <map>

#include <Time/Chronometer.hpp>
#include <Triggers/CallbackScheduler.hpp>
#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerGroup.hpp>

namespace obe::Triggers
{
    /**
     * \brief A TriggerManager that handles all Trigger / TriggerGroup
     */
    class TriggerManager
    {
    private:
        std::map<std::string, std::map<std::string, std::weak_ptr<TriggerGroup>>>
            m_allTriggers;
        std::vector<std::unique_ptr<CallbackScheduler>> m_schedulers;
        Time::Chronometer m_databaseChrono;
        sol::state_view m_lua;

    public:
        explicit TriggerManager(sol::state_view lua);
        /**
         * \brief Get a Trigger contained in the TriggerManager
         * \param space Namespace of the Trigger
         * \param group TriggerGroup of the Trigger
         * \param trigger Name of the Trigger
         * \return A pointer of the Trigger if found
         */
        std::weak_ptr<Trigger> getTrigger(const std::string& space,
            const std::string& group, const std::string& trigger);
        /**
         * \brief Get a list of all names of Trigger instances inside a TriggerGroup
         * \param space Name of the namespace where the TriggerGroup is located
         * \param group Name of the TriggerGroup you want the names of the Trigger
         *        instances from
         * \return A list of names of the Triggers inside the TriggerGroup
         */
        std::vector<std::string> getAllTriggersNameFromTriggerGroup(
            const std::string& space, const std::string& group);
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
        TriggerGroupPtr createTriggerGroup(
            const std::string& space, const std::string& group);
        /**
         * \brief Join an existing TriggerGroup (Throws an error if the
         *        TriggerGroup does not exists or isn't joinable)
         * \param space Namespace of the existing TriggerGroup
         * \param group Name of the TriggerGroup to join
         * \return Pointer to the newly joined TriggerGroup
         */
        TriggerGroupPtr joinTriggerGroup(
            const std::string& space, const std::string& group);
        /**
         * \brief Get all the names of the TriggerGroup in the given Namespace
         * \param space Namespace where to get all the TriggerGroup
         *        names
         * \return A std::vector of std::string containing the names of
         *         all contained TriggerGroup
         */
        std::vector<std::string> getAllTriggersGroupNames(const std::string& space);
        /**
         * \brief Removes an existing namespace
         * \param space Name of the namespace to delete
         */
        void removeNamespace(const std::string& space);
        /**
         * \brief Removes an existing TriggerGroup
         * \param group Pointer to the TriggerGroup to delete
         */
        void removeTriggerGroup(TriggerGroup* group);
        /**
         * \brief Check if a TriggerGroup exists in the TriggerManager
         * \param space Name of the Namespace where to search if the
         *        TriggerGroup exists
         * \param group Name of the TriggerGroup
         *        to search
         * \return true if the TriggerGroup exists, false otherwise
         */
        bool doesTriggerGroupExists(const std::string& space, const std::string& group);
        /**
         * \brief Updates the TriggerManager
         */
        void update();
        /**
         * \brief Clears the TriggerManager
         */
        void clear();

        CallbackScheduler& schedule();
    };
} // namespace obe::Triggers
