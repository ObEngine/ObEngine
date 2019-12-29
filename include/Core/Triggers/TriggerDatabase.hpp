#pragma once

#include <map>

#include <Time/Chronometer.hpp>
#include <Triggers/Trigger.hpp>
#include <Triggers/TriggerGroup.hpp>
#include <Types/Registrable.hpp>
#include <Types/Singleton.hpp>

namespace obe::Triggers
{
    /**
     * \brief A TriggerDatabase that handles all Trigger / TriggerGroup
     * @Bind
     */
    class TriggerDatabase : public Types::Registrable<TriggerDatabase>,
                            public Types::Singleton<TriggerDatabase>
    {
    private:
        std::map<std::string,
            std::map<std::string, std::unique_ptr<TriggerGroup>>>
            m_allTriggers;
        Time::Chronometer m_databaseChrono;
        std::vector<std::unique_ptr<TriggerDelay>> m_delayedTriggers;

    public:
        TriggerDatabase();
        /**
         * \brief Get a Trigger contained in the TriggerDatabase
         * \param namespaceName Namespace of the Trigger
         * \param triggerGroupName TriggerGroup of the Trigger
         * \param triggerName Name of the Trigger
         * \return A pointer of the Trigger if found
         */
        std::weak_ptr<Trigger> getTrigger(const std::string& namespaceName,
            const std::string& triggerGroupName,
            const std::string& triggerName);
        /**
         * \brief Creates a new namespace (Throws an error if the namespace
         * already exists) \param namespaceName Name of the namespace to create
         */
        void createNamespace(const std::string& namespaceName);
        /**
         * \brief Creates a new TriggerGroup (Throws an error if the
         * TriggerGroup already exists) \param namespaceName Namespace where to
         * create the TriggerGroup \param triggerGroupName Name of the new
         * TriggerGroup \return Pointer to the newly created TriggerGroup
         */
        TriggerGroup* createTriggerGroup(const std::string& namespaceName,
            const std::string& triggerGroupName);
        /**
         * \brief Join an existing TriggerGroup (Throws an error if the
         * TriggerGroup doesn't exists or isn't joinable) \param namespaceName
         * Namespace of the existing TriggerGroup \param triggerGroupName Name
         * of the TriggerGroup to join \return Pointer to the newly joined
         * TriggerGroup
         */
        TriggerGroup* joinTriggerGroup(const std::string& namespaceName,
            const std::string& triggerGroupName);
        /**
         * \brief Gets all the names of the Trigger containing the
         * groupNamespace.triggerGroupName \param namespaceName Name of the
         * Namespace \param triggerGroupName Name of the TriggerGroup to get all
         * the Trigger names \return A std::vector of std::string containing all
         * the names of the Trigger in the TriggerGroup
         */
        std::vector<std::string> getAllTriggersNameFromTriggerGroup(
            const std::string& namespaceName,
            const std::string& triggerGroupName);
        /**
         * \brief Get all the names of the TriggerGroup in the given Namespace
         * \param namespaceName Namespace where to get all the TriggerGroup
         * names \return A std::vector of std::string containing the names of
         * all contained TriggerGroup
         */
        std::vector<std::string> getAllTriggersGroupNames(
            const std::string& namespaceName);
        /**
         * \brief Removes an existing namespace
         * \param namespaceName Name of the namespace to delete
         */
        void removeNamespace(const std::string& namespaceName);
        /**
         * \brief Removes an existing TriggerGroup
         * \param trgGroup Pointer to the TriggerGroup to delete
         */
        void removeTriggerGroup(TriggerGroup* trgGroup);
        /**
         * \brief Check if a TriggerGroup exists in the TriggerDatabase
         * \param groupNamespace Name of the Namespace where to search if the
         * TriggerGroup exists \param triggerGroupName Name of the TriggerGroup
         * to search \return
         */
        bool doesTriggerGroupExists(const std::string& groupNamespace,
            const std::string& triggerGroupName);
        /**
         * \brief Updates the TriggerDatabase (Already executed in the main
         * loops)
         */
        void update();
        /**
         * \brief Clears the TriggerDatabase
         */
        void clear();
    };
} // namespace obe::Triggers