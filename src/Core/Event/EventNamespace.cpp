#include <Event/EventNamespace.hpp>

namespace obe::Event
{
    EventNamespaceView::EventNamespaceView(const EventNamespace& eventNamespace)
        : m_namespace(eventNamespace)
    {
    }

    EventGroupPtr EventNamespaceView::joinGroup(const std::string& group) const
    {
        return m_namespace.joinGroup(group);
    }

    EventGroupView EventNamespaceView::getGroup(const std::string& group) const
    {
        return m_namespace.getGroup(group);
    }

    std::vector<std::string> EventNamespaceView::getAllGroupsNames() const
    {
        return m_namespace.getAllGroupsNames();
    }

    bool EventNamespaceView::doesGroupExists(const std::string& group) const
    {
        return m_namespace.doesGroupExists(group);
    }

    EventNamespace::EventNamespace(const std::string& name)
        : m_name(name)
    {
    }

    class EventGroupPtrDeleter
    {
    private:
        EventNamespace* m_eventNamespace;
        EventGroup* m_group;

    public:
        EventGroupPtrDeleter(EventNamespace* eventNamespace);
        void operator()(EventGroup* ptr) const;
    };

    void EventGroupPtrDeleter::operator()(EventGroup* ptr) const
    {
        m_eventNamespace->removeGroup(ptr);
    }

    EventGroupPtrDeleter::EventGroupPtrDeleter(EventNamespace* eventNamespace)
        : m_eventNamespace(eventNamespace)
    {
    }

    EventGroupPtr EventNamespace::createGroup(const std::string& group)
    {
        Debug::Log->debug(
            "<EventNamespace> Creating EventGroup '{}' in Namespace '{}'", group, m_name);
        if (!m_groups.count(group))
        {
            EventGroupPtr newGroup(new EventGroup(m_name, group), EventGroupPtrDeleter(this));
            m_groups.emplace(group, newGroup);
            return newGroup;
        }
        throw Exceptions::EventGroupAlreadyExists(m_name, group, EXC_INFO);
    }

    EventGroupPtr EventNamespace::joinGroup(const std::string& group) const
    {
        Debug::Log->debug(
            "<EventNamespace> Joining EventGroup '{}' in Namespace '{}'", group, m_name);
        if (const auto groupPtr = m_groups.find(group); groupPtr != m_groups.end())
        {
            if (groupPtr->second.lock()->isJoinable())
            {
                return EventGroupPtr(groupPtr->second.lock());
            }
            throw Exceptions::EventGroupNotJoinable(m_name, group, EXC_INFO);
        }

        throw Exceptions::UnknownEventGroup(m_name, group, this->getAllGroupsNames(), EXC_INFO);
    }

    EventGroupView EventNamespace::getGroup(const std::string& group) const
    {
        if (const auto groupPtr = m_groups.find(group); groupPtr != m_groups.end())
        {
            return groupPtr->second.lock()->getView();
        }
        throw Exceptions::UnknownEventGroup(m_name, group, this->getAllGroupsNames(), EXC_INFO);
    }

    std::vector<std::string> EventNamespace::getAllGroupsNames() const
    {
        std::vector<std::string> allNames;
        allNames.reserve(m_groups.size());
        for (const auto& group : m_groups)
        {
            allNames.push_back(group.first);
        }
        return allNames;
    }

    void EventNamespace::removeGroup(EventGroup* group)
    {
        Debug::Log->debug("<EventNamespace> Removing EventGroup '{}' from Namespace '{}'",
            group->getName(), m_name);
        m_groups.erase(group->getName());
    }

    bool EventNamespace::doesGroupExists(const std::string& group) const
    {
        return m_groups.count(group);
    }

    EventNamespaceView EventNamespace::getView() const
    {
        return EventNamespaceView(*this);
    }

    void EventNamespace::setJoinable(bool joinable)
    {
        m_joinable = joinable;
    }

    bool EventNamespace::isJoinable() const
    {
        return m_joinable;
    }
}
