#pragma once

#include <map>

#include <sol/sol.hpp>

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
    // using OnListenerChange = std::function<void(const EventListener&)>;

    class EventBase
    {
    private:
        std::map<std::string, ExternalEventListener> m_listeners;

    protected:
        std::string m_name;
        std::string m_identifier;
        bool m_triggered = false;
        bool m_enabled = true;
        EventProfiler m_profiler;

        template <class EventType> void trigger(const EventType& event);
        template <class EventType, class ListenerType>
        void callListener(const std::string& listenerId, ListenerType&& listener,
            const EventType& event);

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
         * \param listener Listener to register
         */
        void addExternalListener(
            const std::string& id, const ExternalEventListener& listener);
        /**
         * \brief Removes a Listener from the Event
         * \param listener Listener to unregister
         */
        void removeExternalListener(
            const std::string& id, const ExternalEventListener& listener);
        [[nodiscard]] const EventProfiler& getProfiler() const;
    };

    /**
     * \brief A Class that does represents a triggerable event
     */
    template <class EventType> class Event : public EventBase
    {
    private:
        std::map<std::string, CppEventListener<EventType>> m_listeners;

        // std::function<void(const EventListener&)> m_onAddListener;
        // std::function<void(const EventListener&)> m_onRemoveListener;

    protected:
        /**
         * \brief Event callbacks
         */
        void trigger(const EventType& event);
        // void onAddListener(OnListenerChange callback);
        // void onRemoveListener(OnListenerChange callback);

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
         * \param listener Listener to register
         */
        void addListener(
            const std::string& id, const CppEventListener<EventType>& listener);
        /**
         * \brief Removes a Listener from the Event
         * \param listener Listener to unregister
         */
        void removeListener(
            const std::string& id, const CppEventListener<EventType>& listener);

        friend class EventGroup;
    };

    template <class EventType> void EventBase::trigger(const EventType& event)
    {
        for (const auto listener : m_listeners)
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
        CallbackProfiler& profiler = m_profiler[listenerId];
        ScopeProfiler scopeProfiler(profiler);
        try
        {
            listener(event);
        }
        catch (const Exception& e)
        {
            throw Exceptions::EventExecutionError(m_identifier, listenerId, EXC_INFO)
                .nest(e);
        }
    }

    template <class EventType> void Event<EventType>::trigger(const EventType& event)
    {
        Debug::Log->trace("<Event> Executing Event '{}'", m_identifier);

        if (m_enabled)
        {
            m_triggered = true;

            for (const auto listener : m_listeners)
            {
                Debug::Log->trace("<Event> Calling Event Listener '{}' from Event '{}'",
                    listener.first, m_identifier);

                this->callListener(listener.first, listener.second, event);
            }
            EventBase::trigger<EventType>(event);
            m_triggered = false;
        }
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
    }

    template <class EventType>
    void Event<EventType>::removeListener(
        const std::string& id, const CppEventListener<EventType>& listener)
    {
        Debug::Log->trace(
            "<Event> Removing listener '{}' from Event '{}'", id, m_identifier);
        m_listeners.erase(id);
    }
} // namespace obe::Event
