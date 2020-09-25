#include <Debug/Logger.hpp>
#include <Event/EventGroup.hpp>
#include <Event/EventManager.hpp>
#include <Event/Exceptions.hpp>

namespace obe::Event
{
    EventGroup::EventGroup(const std::string& eventNamespace, const std::string& name)
    {
        m_identifier = eventNamespace + "." + name;
        m_name = name;
    }

    std::weak_ptr<Event> EventGroup::get(const std::string& eventName)
    {
        if (const auto event = m_events.find(eventName); event != m_events.end())
        {
            return event->second;
        }
        throw Exceptions::UnknownEvent(
            m_identifier, eventName, this->getEventsNames(), EXC_INFO);
    }

    EventGroup& EventGroup::add(const std::string& eventName)
    {
        Debug::Log->debug("<EventGroup> Add Trigger '{}' to EventGroup '{}'", eventName,
            m_identifier, m_name);
        m_events.emplace(eventName, std::make_unique<Event>(*this, eventName));
        return *this;
    }

    EventGroup& EventGroup::remove(const std::string& eventName)
    {
        Debug::Log->debug("<EventGroup> Remove Trigger '{}' from EventGroup '{}'",
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

    EventGroup& EventGroup::trigger(const std::string& eventName, EventData data)
    {
        Debug::Log->trace(
            "<EventGroup> Trigger '{}' from EventGroup '{}'", eventName, m_identifier);
        this->get(eventName).lock()->execute(data);
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

    std::vector<std::string> EventGroup::getEventsNames()
    {
        std::vector<std::string> names;
        names.reserve(m_events.size());
        std::transform(m_events.begin(), m_events.end(), names.begin(),
            [](const auto& pair) { return pair.first; });
        return names;
    }

    std::vector<Event*> EventGroup::getEvents()
    {
        std::vector<Event*> events;
        for (auto it = m_events.begin(); it != m_events.end(); ++it)
        {
            events.push_back(it->second.get());
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

    void EventGroup::onRegister(const std::string& triggerName, OnListenerChange callback)
    {
        this->get(triggerName).lock()->onRegister(callback);
    }

    void EventGroup::onUnregister(
        const std::string& triggerName, OnListenerChange callback)
    {
        this->get(triggerName).lock()->onUnregister(callback);
    }

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
            for (const auto itr : event->m_profiler)
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
} // namespace obe::Triggers