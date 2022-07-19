#pragma once

#include <Event/Event.hpp>
#include <map>
#include <memory>
#include <vili/node.hpp>

template <typename T>
class HasId
{
private:
    template <typename C>
    static std::true_type test(decltype(&C::id));
    template <typename C>
    static std::false_type test(...);

public:
    enum
    {
        value = sizeof(test<T>(0)) == sizeof(std::true_type)
    };
};

namespace obe::event
{
    class EventGroup;
    class EventGroupView
    {
    private:
        const EventGroup& m_group;

    public:
        EventGroupView(const EventGroup& event_group);
        /**
         * \brief Get the name of all Events contained in the EventGroup
         * \return A std::vector of std::string containing the name of all
         *         Event contained in the EventGroup
         */
        [[nodiscard]] std::vector<std::string> get_events_names() const;
        /**
         * \brief Get all the Events contained in the EventGroup
         * \return A std::vector of Event pointers
         */
        [[nodiscard]] std::vector<EventBase*> get_events() const;
        /**
         * \brief Get the full name of the EventGroup (namespace + name)
         * \return A std::string containing the identifier of the EventGroup
         */
        [[nodiscard]] std::string get_identifier() const;
        /**
         * \brief Get the name of the EventGroup
         * \return A std::string containing the name of the EventGroup
         */
        [[nodiscard]] std::string get_name() const;
        /**
         * \brief Get if the EventGroup is joinable or not
         * \return true if the EventGroup is joinable, false otherwise
         */
        [[nodiscard]] bool is_joinable() const;
        [[nodiscard]] EventBase& get(const std::string& event_name) const;
        /**
         * \brief Checks whether the EventGroup contains an Event with a given name or not
         * \param event_name Name of the Event to check the existence of
         * \return true if the EventGroup contains an Event with the given name, false otherwise
         */
        [[nodiscard]] bool contains(const std::string& event_name) const;
        /**
         * \brief Get a Event contained in the EventGroup
         * \return A pointer to the Event if found (throws an error otherwise)
         */
        template <class EventType>
        Event<EventType>& get() const;
    };

    /**
     * \brief Class used to manage multiple Events
     */
    class EventGroup
    {
    private:
        std::string m_name;
        std::string m_identifier;
        std::map<std::string, std::unique_ptr<EventBase>> m_events;
        bool m_joinable = false;

    public:
        /**
         * \brief Creates a new EventGroup
         * \param event_namespace Name of the Namespace the EventGroup
         *        is in
         * \param name Name of the EventGroup
         */
        explicit EventGroup(const std::string& event_namespace, const std::string& name);
        [[nodiscard]] EventGroupView get_view() const;
        /**
         * \brief Sets if the EventGroup is joinable or not
         * \param joinable true if the EventGroup should be joinable, false
         *        otherwise
         */
        void set_joinable(bool joinable);
        /**
         * \brief Get if the EventGroup is joinable or not
         * \return true if the EventGroup is joinable, false otherwise
         */
        [[nodiscard]] bool is_joinable() const;
        [[nodiscard]] EventBase& get(const std::string& event_name) const;
        /**
         * \brief Get a Event contained in the EventGroup
         * \param event_name Name of the Event to get
         * \return A pointer to the Event if found (throws an error otherwise)
         */
        template <class EventType>
        [[nodiscard]] Event<EventType>& get(const std::string& event_name);
        /**
         * \brief Checks whether the EventGroup contains an Event with a given name or not
         * \param event_name Name of the Event to check the existence of
         * \return true if the EventGroup contains an Event with the given name, false otherwise
         */
        [[nodiscard]] bool contains(const std::string& event_name) const;
        /**
         * \brief Creates a new Event in the EventGroup
         */
        template <class EventType>
        typename std::enable_if_t<HasId<EventType>::value> add();
        template <class EventType>
        void add(const std::string& event_name);
        /**
         * \brief Removes a Event from the EventGroup
         * \param event_name Name of the Event to remove
         */
        void remove(const std::string& event_name);
        /**
         * \brief Triggers a Event
         * \param event event
         * \return Pointer to the EventGroup to chain calls
         */
        template <class EventType>
        typename std::enable_if_t<HasId<EventType>::value> trigger(EventType event);
        /**
         * \brief Triggers a Event
         * \param event_name name of the Event to trigger
         * \param event event
         */
        template <class EventType>
        void trigger(const std::string& event_name, EventType event);
        /**
         * \brief Get the name of all Events contained in the EventGroup
         * \return A std::vector of std::string containing the name of all
         *         Event contained in the EventGroup
         */
        [[nodiscard]] std::vector<std::string> get_events_names() const;
        /**
         * \brief Get all the Events contained in the EventGroup
         * \return A std::vector of Event pointers
         */
        [[nodiscard]] std::vector<EventBase*> get_events() const;
        /**
         * \brief Get the full name of the EventGroup (namespace + name)
         * \return A std::string containing the identifier of the EventGroup
         */
        [[nodiscard]] std::string get_identifier() const;
        /**
         * \brief Get the name of the EventGroup
         * \return A std::string containing the name of the EventGroup
         */
        [[nodiscard]] std::string get_name() const;

        /**
         * \brief Register a callback for when Event::add_listener is called
         */
        void on_add_listener(const std::string& event_name, OnListenerChange callback) const;
        /**
         * \brief Register a callback for when Event::remote_listener is called
         */
        void on_remove_listener(const std::string& event_name, OnListenerChange callback) const;
    };

    template <class EventType>
    Event<EventType>& EventGroupView::get() const
    {
        return m_group.get<EventType>();
    }

    template <class EventType>
    Event<EventType>& EventGroup::get(const std::string& event_name)
    {
        std::string name;
        if (!event_name.empty())
        {
            name = event_name;
        }
        else if constexpr (HasId<EventType>::value)
        {
            name = EventType::id;
        }
        return *static_cast<Event<EventType>*>(m_events.at(name).get());
    }

    template <class EventType>
    typename std::enable_if_t<HasId<EventType>::value> EventGroup::add()
    {
        this->add<EventType>(EventType::id.data());
    }

    template <class EventType>
    void EventGroup::add(const std::string& event_name)
    {
        if (!m_events.contains(event_name))
        {
            debug::Log->debug(
                "<EventGroup> Add Event '{}' to EventGroup '{}'", event_name, m_identifier);
            m_events.emplace(
                event_name, std::make_unique<Event<EventType>>(m_identifier, event_name));
        }
        else
        {
            throw exceptions::EventAlreadyExists(m_identifier, event_name, EXC_INFO);
        }
    }

    template <class EventType>
    typename std::enable_if_t<HasId<EventType>::value> EventGroup::trigger(EventType event)
    {
        this->trigger(EventType::id.data(), event);
    }

    template <class EventType>
    void EventGroup::trigger(const std::string& event_name, EventType event)
    {
        debug::Log->trace(
            "<EventGroup> Triggering Event '{}' from EventGroup '{}'", event_name, m_identifier);
        static_cast<Event<EventType>*>(m_events.at(event_name).get())->trigger(event);
    }

    using EventGroupPtr = std::shared_ptr<EventGroup>;
} // namespace obe::event
