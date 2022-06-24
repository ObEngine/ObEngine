#pragma once

#include <map>

#include <Debug/Logger.hpp>
#include <Event/EventListener.hpp>
#include <Event/Exceptions.hpp>
#include <Time/TimeUtils.hpp>

namespace obe::event
{
    class EventGroup;

    class EventBase
    {
    private:
        std::map<std::string, ExternalEventListener> m_listeners;
        std::vector<std::string> m_garbage_collector;

    protected:
        std::string m_name;
        std::string m_identifier;
        bool m_triggered = false;
        bool m_enabled = true;

        OnListenerChange m_on_add_listener;
        OnListenerChange m_on_remove_listener;

        template <class EventType>
        void trigger(const EventType& event);
        template <class EventType, class ListenerType>
        void call_listener(
            const std::string& listener_id, ListenerType&& listener, const EventType& event);
        void on_add_listener(OnListenerChange callback);
        void on_remove_listener(OnListenerChange callback);
        bool m_garbage_lock = false;
        void collect_garbage();

        friend class EventGroup;

    public:
        /**
         * \brief Creates a new Event
         * \param parent_name Identifier of the parent EventGroup
         * \param name Name of the Event
         * \param initial_state State of the Event when created (enabled /
         *        disabled)
         */
        explicit EventBase(
            const std::string& parent_name, const std::string& name, bool initial_state = false);
        /**
         * \brief Get the State of the Event (enabled / disabled)
         * \return true if the Event is enabled, false otherwise
         */
        [[nodiscard]] bool get_state() const;
        /**
         * \brief Get the name of the Event
         * \return A std::string containing the name of the Event
         */
        [[nodiscard]] std::string get_name() const;
        /**
         * \brief Get the identifier of the Event
         * \return A std::string containing the name of the Event
         */
        [[nodiscard]] std::string get_identifier() const;
        /**
         * \brief Registers a listener that will be called when the Event is triggered
         * \param id of the listener being added
         * \param listener Listener to register
         */
        void add_external_listener(const std::string& id, const ExternalEventListener& listener);
        /**
         * \brief Removes a Listener from the Event
         * \param id id of the Listener to unregister
         */
        void remove_external_listener(const std::string& id);
    };

    /**
     * \brief A Class that does represents a triggerable event
     */
    template <class EventType>
    class Event : public EventBase
    {
    private:
        std::map<std::string, CppEventListener<EventType>> m_listeners;
        std::vector<std::string> m_garbage_collector;

    protected:
        /**
         * \brief Event callbacks
         */
        void trigger(const EventType& event);
        void collect_garbage();

    public:
        /**
         * \brief Creates a new Event
         * \param parent_name Identifier of the parent EventGroup
         * \param name Name of the Event
         * \param initial_state State of the Event when created (enabled /
         *        disabled)
         */
        explicit Event(
            const std::string& parent_name, const std::string& name, bool initial_state = true);

        /**
         * \brief Registers a listener that will be called when the Event is triggered
         * \param id id of the Listener being added
         * \param listener Listener to register
         */
        void add_listener(const std::string& id, const CppEventListener<EventType>& listener);
        /**
         * \brief Removes a Listener from the Event
         * \param id id of the Listener to unregister
         */
        void remove_listener(const std::string& id);

        friend class EventGroup;
    };

    template <class EventType>
    void EventBase::trigger(const EventType& event)
    {
        for (const auto& listener : m_listeners)
        {
            debug::Log->trace("<Event> Calling Event Listener '{}' from Event '{}'", listener.first,
                m_identifier);
            if (std::holds_alternative<LuaEventListener>(listener.second))
            {
                this->call_listener(
                    listener.first, std::get<LuaEventListener>(listener.second), event);
            }
        }
    }

    template <class EventType, class ListenerType>
    void EventBase::call_listener(
        const std::string& listener_id, ListenerType&& listener, const EventType& event)
    {
        if (std::ranges::find(m_garbage_collector, listener_id) != m_garbage_collector.end())
        {
            return;
        }
        try
        {
            listener(event);
        }
        catch (const BaseException& e)
        {
            throw Exceptions::EventExecutionError(m_identifier, listener_id, EXC_INFO).nest(e);
        }
    }

    template <class EventType>
    void Event<EventType>::trigger(const EventType& event)
    {
        debug::Log->trace("<Event> Executing Event '{}'", m_identifier);
        m_garbage_lock = true;

        if (m_enabled)
        {
            m_triggered = true;

            for (const auto& listener : m_listeners)
            {
                debug::Log->trace("<Event> Calling Event Listener '{}' from Event '{}'",
                    listener.first, m_identifier);

                this->call_listener(listener.first, listener.second, event);
            }
            EventBase::trigger<EventType>(event);
            this->collect_garbage();
            EventBase::collect_garbage();
            m_triggered = false;
        }

        m_garbage_lock = false;
    }

    template <class EventType>
    void Event<EventType>::collect_garbage()
    {
        debug::Log->trace("EventListeners Garbage Collection for Event {}", m_identifier);
        for (const std::string& listener_id : m_garbage_collector)
        {
            m_listeners.erase(listener_id);
        }
        m_garbage_collector.clear();
    }

    template <class EventType>
    Event<EventType>::Event(
        const std::string& parent_name, const std::string& name, bool initial_state)
        : EventBase(parent_name, name, initial_state)
    {
    }

    template <class EventType>
    void Event<EventType>::add_listener(
        const std::string& id, const CppEventListener<EventType>& listener)
    {
        debug::Log->trace("<Event> Adding new listener '{}' to Event '{}'", id, m_identifier);
        m_listeners.emplace(id, listener);
        if (m_on_add_listener)
        {
            m_on_add_listener(ListenerChangeState::Added, id);
        }
    }

    template <class EventType>
    void Event<EventType>::remove_listener(const std::string& id)
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
} // namespace obe::event
