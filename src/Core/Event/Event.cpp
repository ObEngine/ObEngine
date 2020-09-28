#include <Event/Event.hpp>
#include <Event/EventGroup.hpp>
#include <Event/Exceptions.hpp>

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
    }

    void EventBase::removeExternalListener(
        const std::string& id, const ExternalEventListener& listener)
    {
        Debug::Log->trace(
            "<Event> Removing listener '{}' from Event '{}'", id, m_identifier);
        m_listeners.erase(id);
    }

    const EventProfiler& EventBase::getProfiler() const
    {
        return m_profiler;
    }

    /*void Event::onAddListener(OnListenerChange callback)
    {
        Debug::Log->trace("<Event> Add onRegister callback to Event '{}'", m_identifier);
        m_onAddListener = callback;
    }

    void Event::onRemoveListener(OnListenerChange callback)
    {
        Debug::Log->trace(
            "<Event> Add onUnregister callback to Event '{}'", m_identifier);
        m_onRemoveListener = callback;
    }*/
} // namespace obe::Event
