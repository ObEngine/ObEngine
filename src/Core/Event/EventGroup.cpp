#include <Debug/Logger.hpp>
#include <Event/EventGroup.hpp>
#include <Event/EventManager.hpp>
#include <Event/Exceptions.hpp>

namespace obe::Event
{
    std::string stripEventTypename(const std::string& typeName)
    {
        const auto signature = Utils::String::split(typeName, "::");
        return signature.back();
    }

    EventGroupView::EventGroupView(const EventGroup& eventGroup)
        : m_group(eventGroup)
    {
    }

    std::vector<std::string> EventGroupView::getEventsNames() const
    {
        return m_group.getEventsNames();
    }

    std::vector<EventBase*> EventGroupView::getEvents() const
    {
        return m_group.getEvents();
    }

    std::string EventGroupView::getIdentifier() const
    {
        return m_group.getIdentifier();
    }

    std::string EventGroupView::getName() const
    {
        return m_group.getName();
    }

    bool EventGroupView::isJoinable() const
    {
        return m_group.isJoinable();
    }

    EventBase& EventGroupView::get(const std::string& eventName) const
    {
        return m_group.get(eventName);
    }

    std::string EventGroup::getEventName(const std::string& baseName)
    {
        if (const auto alias = m_aliases.find(baseName); alias != m_aliases.end())
        {
            return alias->second;
        }
        return baseName;
    }

    EventGroup::EventGroup(const std::string& eventNamespace, const std::string& name)
    {
        m_identifier = eventNamespace + "." + name;
        m_name = name;
    }

    EventGroupView EventGroup::getView() const
    {
        return EventGroupView(*this);
    }

    EventBase& EventGroup::get(const std::string& eventName) const
    {
        if (const auto event = m_events.find(eventName); event != m_events.end())
        {
            return *event->second;
        }
        throw Exceptions::UnknownEvent(
            m_identifier, eventName, this->getEventsNames(), EXC_INFO);
    }

    EventGroup& EventGroup::remove(const std::string& eventName)
    {
        Debug::Log->debug("<EventGroup> Remove Event '{}' from EventGroup '{}'",
            eventName, m_identifier);
        if (m_events.find(eventName) != m_events.end())
            m_events.erase(eventName);
        else
        {
            throw Exceptions::UnknownEvent(
                m_identifier, eventName, this->getEventsNames(), EXC_INFO);
        }
        return *this;
    }

    void EventGroup::setJoinable(bool joinable)
    {
        m_joinable = joinable;
    }

    bool EventGroup::isJoinable() const
    {
        return m_joinable;
    }

    std::vector<std::string> EventGroup::getEventsNames() const
    {
        std::vector<std::string> names;
        names.reserve(m_events.size());
        for (const auto& event : m_events)
        {
            names.push_back(event.first);
        }
        return names;
    }

    std::vector<EventBase*> EventGroup::getEvents() const
    {
        std::vector<EventBase*> events;
        for (auto& event : m_events)
        {
            events.push_back(event.second.get());
        }
        return events;
    }

    std::string EventGroup::getIdentifier() const
    {
        return m_identifier;
    }

    std::string EventGroup::getName() const
    {
        return m_name;
    }

    /*void EventGroup::onAddListener(
        const std::string& eventName, OnListenerChange callback)
    {
        this->get(eventName).lock()->onAddListener(callback);
    }

    void EventGroup::onRemoveListener(
        const std::string& eventName, OnListenerChange callback)
    {
        this->get(eventName).lock()->onRemoveListener(callback);
    }*/

    vili::node EventGroup::getProfilerResults()
    {
        vili::node result = vili::object {};
        for (auto& [eventName, event] : m_events)
        {
            const std::string fullName = m_name + "." + eventName;
            Debug::Log->debug("Dumping {}", fullName);
            result[fullName] = vili::object {};
            Time::TimeUnit totalTime = 0;
            long long int totalHits = 0;
            result.at(fullName).emplace("callbacks", vili::object {});
            vili::node& callbacks = result.at(fullName).at("callbacks");
            for (const auto itr : event->getProfiler())
            {
                callbacks.emplace(itr.first, vili::object {});
                vili::node& callback = callbacks.at(itr.first);
                callback.emplace("time", itr.second.time);
                callback.emplace("hits", vili::integer(itr.second.hits));
                callback.emplace("min", itr.second.min);
                callback.emplace("max", itr.second.max);
                totalTime += itr.second.time;
                totalHits += itr.second.hits;
            }
            result.at(fullName).emplace("time", totalTime);
            result.at(fullName).emplace("hits", totalHits);
        }
        return result;
    }
} // namespace obe::Event