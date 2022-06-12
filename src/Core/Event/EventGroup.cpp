#include <Debug/Logger.hpp>
#include <Event/EventGroup.hpp>

namespace obe::event
{
    EventGroupView::EventGroupView(const EventGroup& event_group)
        : m_group(event_group)
    {
    }

    std::vector<std::string> EventGroupView::get_events_names() const
    {
        return m_group.get_events_names();
    }

    std::vector<EventBase*> EventGroupView::get_events() const
    {
        return m_group.get_events();
    }

    std::string EventGroupView::get_identifier() const
    {
        return m_group.get_identifier();
    }

    std::string EventGroupView::get_name() const
    {
        return m_group.get_name();
    }

    bool EventGroupView::is_joinable() const
    {
        return m_group.is_joinable();
    }

    EventBase& EventGroupView::get(const std::string& event_name) const
    {
        return m_group.get(event_name);
    }

    bool EventGroupView::contains(const std::string& event_name) const
    {
        return m_group.contains(event_name);
    }

    vili::node EventGroupView::get_profiler_results() const
    {
        return m_group.get_profiler_results();
    }

    EventGroup::EventGroup(const std::string& event_namespace, const std::string& name)
    {
        m_identifier = event_namespace + "." + name;
        m_name = name;
    }

    EventGroupView EventGroup::get_view() const
    {
        return EventGroupView(*this);
    }

    EventBase& EventGroup::get(const std::string& event_name) const
    {
        if (const auto event = m_events.find(event_name); event != m_events.end())
        {
            return *event->second;
        }
        throw Exceptions::UnknownEvent(m_identifier, event_name, this->get_events_names(), EXC_INFO);
    }

    bool EventGroup::contains(const std::string& event_name) const
    {
        return (m_events.find(event_name) != m_events.end());
    }

    void EventGroup::remove(const std::string& event_name)
    {
        debug::Log->debug(
            "<EventGroup> Remove Event '{}' from EventGroup '{}'", event_name, m_identifier);
        if (m_events.find(event_name) != m_events.end())
            m_events.erase(event_name);
        else
        {
            throw Exceptions::UnknownEvent(
                m_identifier, event_name, this->get_events_names(), EXC_INFO);
        }
    }

    void EventGroup::set_joinable(bool joinable)
    {
        m_joinable = joinable;
    }

    bool EventGroup::is_joinable() const
    {
        return m_joinable;
    }

    std::vector<std::string> EventGroup::get_events_names() const
    {
        std::vector<std::string> names;
        names.reserve(m_events.size());
        for (const auto& event : m_events)
        {
            names.push_back(event.first);
        }
        return names;
    }

    std::vector<EventBase*> EventGroup::get_events() const
    {
        std::vector<EventBase*> events;
        for (auto& event : m_events)
        {
            events.push_back(event.second.get());
        }
        return events;
    }

    std::string EventGroup::get_identifier() const
    {
        return m_identifier;
    }

    std::string EventGroup::get_name() const
    {
        return m_name;
    }

    void EventGroup::on_add_listener(const std::string& event_name, OnListenerChange callback) const
    {
        this->get(event_name).on_add_listener(callback);
    }

    void EventGroup::on_remove_listener(const std::string& event_name, OnListenerChange callback) const
    {
        this->get(event_name).on_remove_listener(callback);
    }

    vili::node EventGroup::get_profiler_results() const
    {
        vili::node result = vili::object {};
        for (auto& [event_name, event] : m_events)
        {
            const std::string full_name = m_name + "." + event_name;
            debug::Log->debug("Dumping {}", full_name);
            result[full_name] = vili::object {};
            Time::TimeUnit total_time = 0;
            long long int total_hits = 0;
            result.at(full_name).emplace("callbacks", vili::object {});
            vili::node& callbacks = result.at(full_name).at("callbacks");
            for (const auto& [event_id, event_records] : event->get_profiler())
            {
                callbacks.emplace(event_id, vili::object {});
                vili::node& callback = callbacks.at(event_id);
                callback.emplace("time", event_records.time);
                callback.emplace("hits", vili::integer(event_records.hits));
                callback.emplace("min", event_records.min);
                callback.emplace("max", event_records.max);
                total_time += event_records.time;
                total_hits += event_records.hits;
            }
            result.at(full_name).emplace("time", total_time);
            result.at(full_name).emplace("hits", total_hits);
        }
        return result;
    }
} // namespace obe::event
