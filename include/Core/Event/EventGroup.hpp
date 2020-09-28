#pragma once

#include <map>
#include <memory>
#include <typeinfo>

#include <vili/node.hpp>

#include <Event/Event.hpp>
#include <Event/EventData.hpp>

namespace obe::Event
{
    std::string stripEventTypename(const std::string& typeName);

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
         * \brief Get a Event contained in the EventGroup
         * \return A pointer to the Event if found (throws an error otherwise)
         */
        template <class EventType> Event<EventType>& get() const;
    };

    /**
     * \brief Class used to manage multiple Events
     */
    class EventGroup
    {
    private:
        std::string m_name;
        std::string m_identifier;
        std::map<std::string, std::string> m_aliases;
        std::map<std::string, std::unique_ptr<EventBase>> m_events;
        bool m_joinable = false;

        std::string getEventName(const std::string& baseName);

    public:
        /**
         * \brief Creates a new EventGroup
         * \param eventNamespace Name of the Namespace the EventGroup
         *        is in
         * \param name Name of the EventGroup
         */
        explicit EventGroup(const std::string& eventNamespace, const std::string& name);
        EventGroupView getView() const;
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
        template <class EventType>[[nodiscard]] Event<EventType>& get();
        /**
         * \brief Creates a new Event in the EventGroup
         * \param eventName Name of the Event to create
         * \return Pointer to the EventGroup to chain calls
         */
        template <class EventType> EventGroup& add(const std::string& eventName = "");
        /**
         * \brief Removes a Event from the EventGroup
         * \param eventName Name of the Event to remove
         * \return Pointer to the EventGroup to chain calls
         */
        EventGroup& remove(const std::string& eventName);
        /**
         * \brief Triggers a Event
         * \param event event
         * \return Pointer to the EventGroup to chain calls
         */
        template <class EventType> EventGroup& trigger(EventType event);
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
        // void onAddListener(const std::string& eventName, OnListenerChange callback);
        /**
         * \brief Register a callback for when Event::removeListener is called
         */
        // void onRemoveListener(const std::string& eventName, OnListenerChange callback);
        vili::node getProfilerResults();
    };

    template <class EventType> Event<EventType>& EventGroupView::get() const
    {
        return m_group.get<EventType>();
    }

    template <class EventType> Event<EventType>& EventGroup::get()
    {
        const std::string name = this->getEventName(typeid(EventType).name());
        return *static_cast<Event<EventType>*>(m_events.at(name).get());
    }

    template <class EventType> EventGroup& EventGroup::add(const std::string& eventName)
    {
        std::string name = typeid(EventType).name();
        if (!eventName.empty())
        {
            m_aliases[name] = eventName;
            name = eventName;
        }
        else
        {
            const std::string strippedTypename = stripEventTypename(name);
            m_aliases[name] = strippedTypename;
            name = strippedTypename;
        }
        Debug::Log->debug(
            "<EventGroup> Add Event '{}' to EventGroup '{}'", name, m_identifier);
        m_events.emplace(name, std::make_unique<Event<EventType>>(m_identifier, name));
        return *this;
    }

    template <class EventType> EventGroup& EventGroup::trigger(EventType event)
    {
        const std::string name = this->getEventName(typeid(event).name());
        Debug::Log->trace("<EventGroup> Triggering Event '{}' from EventGroup '{}'", name,
            m_identifier);
        static_cast<Event<EventType>*>(m_events.at(name).get())->trigger(event);
        return *this;
    }

    using EventGroupPtr = std::shared_ptr<EventGroup>;
} // namespace obe::Event