#pragma once

#include <Event/EventGroup.hpp>

namespace obe::Event
{
    class EventNamespace;

    class EventNamespaceView
    {
    private:
        const EventNamespace& m_namespace;

    public:
        EventNamespaceView(const EventNamespace& eventNamespace);
        EventGroupView getGroup(const std::string& group) const;
        /**
         * \brief Get all the names of the EventGroup in the given Namespace
         * \return A std::vector of std::string containing the names of
         *         all contained EventGroup
         */
        [[nodiscard]] std::vector<std::string> getAllGroupsNames() const;
        /**
         * \brief Check if an EventGroup exists in the EventNamespace
         * \param group Name of the EventGroup
         *        to search
         * \return true if the EventGroup exists, false otherwise
         */
        bool doesGroupExists(const std::string& group) const;
    };

    class EventNamespace
    {
    private:
        std::string m_name;
        std::map<std::string, std::weak_ptr<EventGroup>> m_groups;

    public:
        explicit EventNamespace(const std::string& name);
        /**
         * \brief Creates a new EventGroup (Throws an error if the
         *        EventGroup already exists)
         * \param group Name of the new EventGroup
         * \return Managed pointer to the newly created EventGroup
         */
        EventGroupPtr createGroup(const std::string& group);
        /**
         * \brief Join an existing EventGroup (Throws an error if the
         *        EventGroup does not exists or isn't joinable)
         * \param group Name of the EventGroup to join
         * \return Pointer to the newly joined EventGroup
         */
        EventGroupPtr joinGroup(const std::string& group);
        EventGroupView getGroup(const std::string& group) const;
        /**
         * \brief Get all the names of the EventGroup in the given Namespace
         * \return A std::vector of std::string containing the names of
         *         all contained EventGroup
         */
        [[nodiscard]] std::vector<std::string> getAllGroupsNames() const;
        /**
         * \brief Removes an existing EventGroup
         * \param group Pointer to the EventGroup to delete
         */
        void removeGroup(EventGroup* group);
        /**
         * \brief Check if an EventGroup exists in the EventNamespace
         * \param group Name of the EventGroup
         *        to search
         * \return true if the EventGroup exists, false otherwise
         */
        bool doesGroupExists(const std::string& group) const;
        [[nodiscard]] EventNamespaceView getView() const;
    };
}