#pragma once

#include <map>
#include <memory>

#include <vili/node.hpp>

#include <Event/Event.hpp>

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

namespace obe::Event
{
    class EventGroup;
    class EventGroupView
    {
    private:
        const EventGroup& m_group;

    public:
        EventGroupView(const EventGroup& eventGroup);
        /**
         * \brief Get the name of all Events contained in the EventGroup
         * \return A std::vector of std::string containing the name of all
         *         Event contained in the EventGroup
         */
        [[nodiscard]] std::vector<std::string> getEventsNames() const;
        /**
         * \brief Get all the Events contained in the EventGroup
         * \return A std::vector of Event pointers
         */
        [[nodiscard]] std::vector<EventBase*> getEvents() const;
        /**
         * \brief Get the full name of the EventGroup (namespace + name)
         * \return A std::string containing the identifier of the EventGroup
         */
        [[nodiscard]] std::string getIdentifier() const;
        /**
         * \brief Get the name of the EventGroup
         * \return A std::string containing the name of the EventGroup
         */
        [[nodiscard]] std::string getName() const;
        /**
         * \brief Get if the EventGroup is joinable or not
         * \return true if the EventGroup is joinable, false otherwise
         */
        [[nodiscard]] bool isJoinable() const;
        [[nodiscard]] EventBase& get(const std::string& eventName) const;
        /**
         * \brief Checks whether the EventGroup contains an Event with a given name or not
         * \param eventName Name of the Event to check the existence of
         * \return true if the EventGroup contains an Event with the given name, false otherwise
         */
        [[nodiscard]] bool contains(const std::string& eventName) const;
        /**
         * \brief Get a Event contained in the EventGroup
         * \return A pointer to the Event if found (throws an error otherwise)
         */
        template <class EventType>
        Event<EventType>& get() const;
        vili::node getProfilerResults() const;
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
         * \param eventNamespace Name of the Namespace the EventGroup
         *        is in
         * \param name Name of the EventGroup
         */
        explicit EventGroup(const std::string& eventNamespace, const std::string& name);
        [[nodiscard]] EventGroupView getView() const;
        /**
         * \brief Sets if the EventGroup is joinable or not
         * \param joinable true if the EventGroup should be joinable, false
         *        otherwise
         */
        void setJoinable(bool joinable);
        /**
         * \brief Get if the EventGroup is joinable or not
         * \return true if the EventGroup is joinable, false otherwise
         */
        [[nodiscard]] bool isJoinable() const;
        [[nodiscard]] EventBase& get(const std::string& eventName) const;
        /**
         * \brief Get a Event contained in the EventGroup
         * \param eventName Name of the Event to get
         * \return A pointer to the Event if found (throws an error otherwise)
         */
        template <class EventType>
        [[nodiscard]] Event<EventType>& get(const std::string& eventName);
        /**
         * \brief Checks whether the EventGroup contains an Event with a given name or not
         * \param eventName Name of the Event to check the existence of
         * \return true if the EventGroup contains an Event with the given name, false otherwise
         */
        [[nodiscard]] bool contains(const std::string& eventName) const;
        /**
         * \brief Creates a new Event in the EventGroup
         * \param eventName Name of the Event to create
         */
        template <class EventType>
        typename std::enable_if_t<HasId<EventType>::value> add();
        template <class EventType>
        void add(const std::string& eventName);
        /**
         * \brief Removes a Event from the EventGroup
         * \param eventName Name of the Event to remove
         * \return Pointer to the EventGroup to chain calls
         */
        void remove(const std::string& eventName);
        /**
         * \brief Triggers a Event
         * \param event event
         * \return Pointer to the EventGroup to chain calls
         */
        template <class EventType>
        typename std::enable_if_t<HasId<EventType>::value> trigger(EventType event);
        /**
         * \brief Triggers a Event
         * \param eventName name of the Event to trigger
         * \param event event
         * \return Pointer to the EventGroup to chain calls
         */
        template <class EventType>
        void trigger(const std::string& eventName, EventType event);
        /**
         * \brief Get the name of all Events contained in the EventGroup
         * \return A std::vector of std::string containing the name of all
         *         Event contained in the EventGroup
         */
        [[nodiscard]] std::vector<std::string> getEventsNames() const;
        /**
         * \brief Get all the Events contained in the EventGroup
         * \return A std::vector of Event pointers
         */
        [[nodiscard]] std::vector<EventBase*> getEvents() const;
        /**
         * \brief Get the full name of the EventGroup (namespace + name)
         * \return A std::string containing the identifier of the EventGroup
         */
        [[nodiscard]] std::string getIdentifier() const;
        /**
         * \brief Get the name of the EventGroup
         * \return A std::string containing the name of the EventGroup
         */
        [[nodiscard]] std::string getName() const;

        /**
         * \brief Register a callback for when Event::addListener is called
         */
        void onAddListener(const std::string& eventName, OnListenerChange callback) const;
        /**
         * \brief Register a callback for when Event::removeListener is called
         */
        void onRemoveListener(const std::string& eventName, OnListenerChange callback) const;
        vili::node getProfilerResults() const;
    };

    template <class EventType>
    Event<EventType>& EventGroupView::get() const
    {
        return m_group.get<EventType>();
    }

    template <class EventType>
    Event<EventType>& EventGroup::get(const std::string& eventName)
    {
        std::string name;
        if (!eventName.empty())
        {
            name = eventName;
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
    void EventGroup::add(const std::string& eventName)
    {
        if (!m_events.count(eventName))
        {
            Debug::Log->debug(
                "<EventGroup> Add Event '{}' to EventGroup '{}'", eventName, m_identifier);
            m_events.emplace(
                eventName, std::make_unique<Event<EventType>>(m_identifier, eventName));
        }
        else
        {
            throw Exceptions::EventAlreadyExists(m_identifier, eventName, EXC_INFO);
        }
    }

    template <class EventType>
    typename std::enable_if_t<HasId<EventType>::value> EventGroup::trigger(EventType event)
    {
        this->trigger(EventType::id.data(), event);
    }

    template <class EventType>
    void EventGroup::trigger(const std::string& eventName, EventType event)
    {
        Debug::Log->trace(
            "<EventGroup> Triggering Event '{}' from EventGroup '{}'", eventName, m_identifier);
        static_cast<Event<EventType>*>(m_events.at(eventName).get())->trigger(event);
    }

    using EventGroupPtr = std::shared_ptr<EventGroup>;
} // namespace obe::Event
