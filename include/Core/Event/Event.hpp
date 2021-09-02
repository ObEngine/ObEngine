#pragma once

#include <map>

#include <Debug/Logger.hpp>
#include <Event/EventListener.hpp>
#include <Event/Exceptions.hpp>
#include <Time/TimeUtils.hpp>


namespace obe::Event
{
    class EventGroup;

    class CallbackProfiler
    {
    public:
        std::uint64_t hits = 0;
        Time::TimeUnit time = 0;
        Time::TimeUnit min = 0;
        Time::TimeUnit max = 0;
    };

    class ScopeProfiler
    {
    private:
        const Time::TimeUnit m_start;
        CallbackProfiler& m_results;

    public:
        ScopeProfiler(CallbackProfiler& results);
        ~ScopeProfiler();
    };

    using EventProfiler = std::unordered_map<std::string, CallbackProfiler>;

    class EventBase
    {
    private:
        std::map<std::string, ExternalEventListener> m_listeners;
        std::vector<std::string> m_garbageCollector;

    protected:
        std::string m_name;
        std::string m_identifier;
        bool m_triggered = false;
        bool m_enabled = true;
        EventProfiler m_profiler;
        OnListenerChange m_onAddListener;
        OnListenerChange m_onRemoveListener;

        template <class EventType> void trigger(const EventType& event);
        template <class EventType, class ListenerType>
        void callListener(const std::string& listenerId, ListenerType&& listener,
            const EventType& event);
        void onAddListener(OnListenerChange callback);
        void onRemoveListener(OnListenerChange callback);
        bool m_garbageLock = false;
        void collectGarbage();

        friend class EventGroup;

    public:
        /**
         * \brief Creates a new Event
         * \param parentName Identifier of the parent EventGroup
         * \param name Name of the Event
         * \param startState State of the Event when created (enabled /
         *        disabled)
         */
        explicit EventBase(const std::string& parentName, const std::string& name,
            bool startState = false);
        /**
         * \brief Get the State of the Event (enabled / disabled)
         * \return true if the Event is enabled, false otherwise
         */
        [[nodiscard]] bool getState() const;
        /**
         * \brief Get the name of the Event
         * \return A std::string containing the name of the Event
         */
        [[nodiscard]] std::string getName() const;
        /**
         * \brief Get the identifier of the Event
         * \return A std::string containing the name of the Event
         */
        [[nodiscard]] std::string getIdentifier() const;
        /**
         * \brief Registers a listener that will be called when the Event is triggered
         * \param id of the listener being added
         * \param listener Listener to register
         */
        void addExternalListener(
            const std::string& id, const ExternalEventListener& listener);
        /**
         * \brief Removes a Listener from the Event
         * \param id id of the Listener to unregister
         */
        void removeExternalListener(const std::string& id);
        [[nodiscard]] const EventProfiler& getProfiler() const;
    };

    /**
     * \brief A Class that does represents a triggerable event
     */
    template <class EventType> class Event : public EventBase
    {
    private:
        std::map<std::string, CppEventListener<EventType>> m_listeners;
        std::vector<std::string> m_garbageCollector;

    protected:
        /**
         * \brief Event callbacks
         */
        void trigger(const EventType& event);
        void collectGarbage();

    public:
        /**
         * \brief Creates a new Event
         * \param parentName Identifier of the parent EventGroup
         * \param name Name of the Event
         * \param startState State of the Event when created (enabled /
         *        disabled)
         */
        explicit Event(const std::string& parentName, const std::string& name,
            bool startState = true);

        /**
         * \brief Registers a listener that will be called when the Event is triggered
         * \param id id of the Listener being added
         * \param listener Listener to register
         */
        void addListener(
            const std::string& id, const CppEventListener<EventType>& listener);
        /**
         * \brief Removes a Listener from the Event
         * \param id id of the Listener to unregister
         */
        void removeListener(const std::string& id);

        friend class EventGroup;
    };

    template <class EventType> void EventBase::trigger(const EventType& event)
    {
        for (const auto& listener : m_listeners)
        {
            Debug::Log->trace("<Event> Calling Event Listener '{}' from Event '{}'",
                listener.first, m_identifier);
            if (std::holds_alternative<LuaEventListener>(listener.second))
            {
                this->callListener(
                    listener.first, std::get<LuaEventListener>(listener.second), event);
            }
        }
    }

    template <class EventType, class ListenerType>
    void EventBase::callListener(
        const std::string& listenerId, ListenerType&& listener, const EventType& event)
    {
        if (std::find(m_garbageCollector.begin(), m_garbageCollector.end(), listenerId)
            != m_garbageCollector.end())
        {
            return;
        }
        CallbackProfiler& profiler = m_profiler[listenerId];
        ScopeProfiler scopeProfiler(profiler);
        try
        {
            listener(event);
        }
        catch (const BaseException& e)
        {
            throw Exceptions::EventExecutionError(m_identifier, listenerId, EXC_INFO)
                .nest(e);
        }
    }

    template <class EventType> void Event<EventType>::trigger(const EventType& event)
    {
        Debug::Log->trace("<Event> Executing Event '{}'", m_identifier);
        m_garbageLock = true;

        if (m_enabled)
        {
            m_triggered = true;

            for (const auto& listener : m_listeners)
            {
                Debug::Log->trace("<Event> Calling Event Listener '{}' from Event '{}'",
                    listener.first, m_identifier);

                this->callListener(listener.first, listener.second, event);
            }
            EventBase::trigger<EventType>(event);
            this->collectGarbage();
            EventBase::collectGarbage();
            m_triggered = false;
        }

        m_garbageLock = false;
    }

    template <class EventType>
    void Event<EventType>::collectGarbage()
    {
        Debug::Log->trace(
            "EventListeners Garbage Collection for Event {}", m_identifier);
        for (const std::string& listenerId : m_garbageCollector)
        {
            m_listeners.erase(listenerId);
        }
        m_garbageCollector.clear();
    }

    template <class EventType>
    Event<EventType>::Event(
        const std::string& parentName, const std::string& name, bool startState)
        : EventBase(parentName, name, startState)
    {
    }

    template <class EventType>
    void Event<EventType>::addListener(
        const std::string& id, const CppEventListener<EventType>& listener)
    {
        Debug::Log->trace(
            "<Event> Adding new listener '{}' to Event '{}'", id, m_identifier);
        m_listeners.emplace(id, listener);
        if (m_onAddListener)
        {
            m_onAddListener(ListenerChangeState::Added, id);
        }
    }

    template <class EventType>
    void Event<EventType>::removeListener(const std::string& id)
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
} // namespace obe::Event
