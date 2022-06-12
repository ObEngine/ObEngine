#include <Event/Event.hpp>
#include <utility>

namespace obe::event
{
    ScopeProfiler::ScopeProfiler(CallbackProfiler& results)
        : m_start(Time::epoch())
        , m_results(results)
    {
    }

    ScopeProfiler::~ScopeProfiler()
    {
        const Time::TimeUnit duration = Time::epoch() - m_start;

        m_results.time += duration;
        ++m_results.hits;
        if (duration < m_results.min || m_results.min == 0)
        {
            m_results.min = duration;
        }
        if (duration > m_results.max)
        {
            m_results.max = duration;
        }
    }

    void EventBase::on_add_listener(OnListenerChange callback)
    {
        m_on_add_listener = std::move(callback);
    }

    void EventBase::on_remove_listener(OnListenerChange callback)
    {
        m_on_remove_listener = std::move(callback);
    }

    void EventBase::collect_garbage()
    {
        debug::Log->trace(
            "EventListeners Garbage Collection for Event {} [External]", m_identifier);
        for (const std::string& listener_id : m_garbage_collector)
        {
            debug::Log->trace("  - Garbage Collecting listener {}", listener_id);
            m_listeners.erase(listener_id);
        }
        m_garbage_collector.clear();
    }

    EventBase::EventBase(const std::string& parent_name, const std::string& name, bool initial_state)
        : m_name(name)
        , m_enabled(initial_state)
    {
        m_identifier = fmt::format("{}.{}", parent_name, m_name);

        debug::Log->trace("<Event> Creating Event '{}' @{}", m_identifier, fmt::ptr(this));
    }

    bool EventBase::get_state() const
    {
        return m_enabled;
    }

    std::string EventBase::get_name() const
    {
        return m_name;
    }

    std::string EventBase::get_identifier() const
    {
        return m_identifier;
    }

    void EventBase::add_external_listener(
        const std::string& id, const ExternalEventListener& listener)
    {
        debug::Log->trace("<Event> Adding new listener '{}' to Event '{}'", id, m_identifier);
        m_listeners.emplace(id, listener);
        if (m_on_add_listener)
        {
            m_on_add_listener(ListenerChangeState::Added, id);
        }
    }

    void EventBase::remove_external_listener(const std::string& id)
    {
        debug::Log->trace("<Event> Removing listener '{}' from Event '{}'", id, m_identifier);
        if (m_garbage_lock)
            m_garbage_collector.push_back(id);
        else
            m_listeners.erase(id);
        if (m_on_remove_listener)
        {
            m_on_remove_listener(ListenerChangeState::Removed, id);
        }
    }

    const EventProfiler& EventBase::get_profiler() const
    {
        return m_profiler;
    }
} // namespace obe::event
