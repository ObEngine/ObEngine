#include <Event/EventNamespace.hpp>

namespace obe::event
{
    EventNamespaceView::EventNamespaceView(const EventNamespace& event_namespace)
        : m_namespace(event_namespace)
    {
    }

    EventGroupPtr EventNamespaceView::join_group(const std::string& group) const
    {
        return m_namespace.join_group(group);
    }

    EventGroupView EventNamespaceView::get_group(const std::string& group) const
    {
        return m_namespace.get_group(group);
    }

    std::vector<std::string> EventNamespaceView::get_all_groups_names() const
    {
        return m_namespace.get_all_groups_names();
    }

    bool EventNamespaceView::does_group_exists(const std::string& group) const
    {
        return m_namespace.does_group_exists(group);
    }

    std::string EventNamespaceView::get_name() const
    {
        return m_namespace.get_name();
    }

    class EventGroupPtrDeleter
    {
    private:
        EventNamespace* m_eventNamespace;
        EventGroup* m_group;

    public:
        EventGroupPtrDeleter(EventNamespace* event_namespace);
        void operator()(EventGroup* ptr) const;
    };

    void EventGroupPtrDeleter::operator()(EventGroup* ptr) const
    {
        m_eventNamespace->remove_group(ptr);
    }

    EventGroupPtrDeleter::EventGroupPtrDeleter(EventNamespace* event_namespace)
        : m_eventNamespace(event_namespace)
    {
    }

    EventNamespace::EventNamespace(const std::string& name, ConstructorKey)
        : m_name(name)
    {
    }

    EventGroupPtr EventNamespace::create_group(const std::string& group)
    {
        debug::Log->debug(
            "<EventNamespace> Creating EventGroup '{}' in Namespace '{}'", group, m_name);
        if (!m_groups.contains(group))
        {
            EventGroupPtr new_group(new EventGroup(*this, group), EventGroupPtrDeleter(this));
            m_groups.emplace(group, new_group);
            return new_group;
        }
        throw exceptions::EventGroupAlreadyExists(m_name, group);
    }

    EventGroupPtr EventNamespace::join_group(const std::string& group) const
    {
        debug::Log->debug(
            "<EventNamespace> Joining EventGroup '{}' in Namespace '{}'", group, m_name);
        if (const auto group_ptr = m_groups.find(group); group_ptr != m_groups.end())
        {
            if (group_ptr->second.lock()->is_joinable())
            {
                return EventGroupPtr(group_ptr->second.lock());
            }
            throw exceptions::EventGroupNotJoinable(m_name, group);
        }

        throw exceptions::UnknownEventGroup(m_name, group, this->get_all_groups_names());
    }

    EventGroupView EventNamespace::get_group(const std::string& group) const
    {
        if (const auto group_ptr = m_groups.find(group); group_ptr != m_groups.end())
        {
            return group_ptr->second.lock()->get_view();
        }
        throw exceptions::UnknownEventGroup(m_name, group, this->get_all_groups_names());
    }

    std::vector<std::string> EventNamespace::get_all_groups_names() const
    {
        std::vector<std::string> all_names;
        all_names.reserve(m_groups.size());
        for (const auto& group : m_groups)
        {
            all_names.push_back(group.first);
        }
        return all_names;
    }

    void EventNamespace::remove_group(EventGroup* group)
    {
        debug::Log->debug("<EventNamespace> Removing EventGroup '{}' from Namespace '{}'",
            group->get_name(), m_name);
        m_groups.erase(group->get_name());
    }

    bool EventNamespace::does_group_exists(const std::string& group) const
    {
        return m_groups.contains(group);
    }

    EventNamespaceView EventNamespace::get_view() const
    {
        return EventNamespaceView(*this);
    }

    void EventNamespace::set_joinable(bool joinable)
    {
        m_joinable = joinable;
    }

    bool EventNamespace::is_joinable() const
    {
        return m_joinable;
    }

    std::string EventNamespace::get_name() const
    {
        return m_name;
    }
}
