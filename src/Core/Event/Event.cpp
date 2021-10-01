#include <Event/Event.hpp>

namespace obe::Event
{
    ScopeProfiler::ScopeProfiler(CallbackProfiler& results)
        : m_results(results)
        , m_start(Time::epoch())
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

    void EventBase::onAddListener(OnListenerChange callback)
    {
        m_onAddListener = callback;
    }

    void EventBase::onRemoveListener(OnListenerChange callback)
    {
        m_onRemoveListener = std::move(callback);
    }

    void EventBase::collectGarbage()
    {
        Debug::Log->trace("EventListeners Garbage Collection for Event {} [External]", m_identifier);
        for (const std::string& listenerId : m_garbageCollector)
        {
            Debug::Log->trace("  - Garbage Collecting listener {}",
                listenerId);
            m_listeners.erase(listenerId);
        }
        m_garbageCollector.clear();
    }


    EventBase::EventBase(
        const std::string& parentName, const std::string& name, bool startState)
    {
        m_name = name;
        m_identifier = fmt::format("{}.{}", parentName, m_name);
        m_enabled = startState;
        Debug::Log->trace(
            "<Event> Creating Event '{}' @{}", m_identifier, fmt::ptr(this));
    }

    bool EventBase::getState() const
    {
        return m_enabled;
    }

    std::string EventBase::getName() const
    {
        return m_name;
    }

    std::string EventBase::getIdentifier() const
    {
        return m_identifier;
    }

    void EventBase::addExternalListener(
        const std::string& id, const ExternalEventListener& listener)
    {
        Debug::Log->trace(
            "<Event> Adding new listener '{}' to Event '{}'", id, m_identifier);
        m_listeners.emplace(id, listener);
        if (m_onAddListener)
        {
            m_onAddListener(ListenerChangeState::Added, id);
        }
    }

    void EventBase::removeExternalListener(const std::string& id)
    {
        Debug::Log->trace(
            "<Event> Removing listener '{}' from Event '{}'", id, m_identifier);
        if (m_garbageLock)
            m_garbageCollector.push_back(id);
        else
            m_listeners.erase(id);
        if (m_onRemoveListener)
        {
            m_onRemoveListener(ListenerChangeState::Removed, id);
        }
    }

    const EventProfiler& EventBase::getProfiler() const
    {
        return m_profiler;
    }
} // namespace obe::Event
