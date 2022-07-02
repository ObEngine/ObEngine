#pragma once

#include <Event/EventGroup.hpp>

namespace obe::event
{
    class EventNamespace;

    class EventNamespaceView
    {
    private:
        const EventNamespace& m_namespace;

    public:
        EventNamespaceView(const EventNamespace& event_namespace);
        [[nodiscard]] EventGroupPtr join_group(const std::string& group) const;
        [[nodiscard]] EventGroupView get_group(const std::string& group) const;
        /**
         * \brief Get all the names of the EventGroup in the given Namespace
         * \return A std::vector of std::string containing the names of
         *         all contained EventGroup
         */
        [[nodiscard]] std::vector<std::string> get_all_groups_names() const;
        /**
         * \brief Check if an EventGroup exists in the EventNamespace
         * \param group Name of the EventGroup
         *        to search
         * \return true if the EventGroup exists, false otherwise
         */
        [[nodiscard]] bool does_group_exists(const std::string& group) const;
    };

    class EventNamespace
    {
    private:
        std::string m_name;
        std::map<std::string, std::weak_ptr<EventGroup>> m_groups;
        bool m_joinable = false;

    public:
        explicit EventNamespace(const std::string& name);
        /**
         * \brief Creates a new EventGroup (Throws an error if the
         *        EventGroup already exists)
         * \param group Name of the new EventGroup
         * \return Managed pointer to the newly created EventGroup
         */
        EventGroupPtr create_group(const std::string& group);
        /**
         * \brief Join an existing EventGroup (Throws an error if the
         *        EventGroup does not exists or isn't joinable)
         * \param group Name of the EventGroup to join
         * \return Pointer to the newly joined EventGroup
         */
        [[nodiscard]] EventGroupPtr join_group(const std::string& group) const;
        [[nodiscard]] EventGroupView get_group(const std::string& group) const;
        /**
         * \brief Get all the names of the EventGroup in the given Namespace
         * \return A std::vector of std::string containing the names of
         *         all contained EventGroup
         */
        [[nodiscard]] std::vector<std::string> get_all_groups_names() const;
        /**
         * \brief Removes an existing EventGroup
         * \param group Pointer to the EventGroup to delete
         */
        void remove_group(EventGroup* group);
        /**
         * \brief Check if an EventGroup exists in the EventNamespace
         * \param group Name of the EventGroup
         *        to search
         * \return true if the EventGroup exists, false otherwise
         */
        [[nodiscard]] bool does_group_exists(const std::string& group) const;
        [[nodiscard]] EventNamespaceView get_view() const;
        /**
         * \brief Sets if the EventNamespace is joinable or not
         * \param joinable true if the EventNamespace should be joinable, false
         *        otherwise
         */
        void set_joinable(bool joinable);
        /**
         * \brief Get if the EventNamespace is joinable or not
         * \return true if the EventNamespace is joinable, false otherwise
         */
        [[nodiscard]] bool is_joinable() const;
    };
} // namespace obe::event
