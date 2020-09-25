#pragma once

#include <map>
#include <memory>

#include <vili/node.hpp>

#include <Event/Event.hpp>
#include <Event/EventData.hpp>

namespace obe::Event
{
    /**
     * \brief Class used to manage multiple Events
     */
    class EventGroup
    {
    private:
        std::string m_name;
        std::string m_identifier;
        std::map<std::string, std::shared_ptr<Event>> m_events;
        bool m_joinable = false;
        friend class Trigger;
        friend class TriggerManager;

    public:
        /**
         * \brief Creates a new EventGroup
         * \param eventNamespace Name of the Namespace the EventGroup
         *        is in
         * \param name Name of the EventGroup
         */
        explicit EventGroup(const std::string& eventNamespace, const std::string& name);
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
        /**
         * \brief Get a Trigger contained in the EventGroup
         * \param eventName Name of the Trigger to get
         * \return A pointer to the Trigger if found (throws an error otherwise)
         */
        std::weak_ptr<Event> get(const std::string& eventName);
        /**
         * \brief Creates a new Trigger in the EventGroup
         * \param eventName Name of the Trigger to create
         * \return Pointer to the EventGroup to chain calls
         */
        EventGroup& add(const std::string& eventName);
        /**
         * \brief Removes a Trigger from the EventGroup
         * \param eventName Name of the Trigger to remove
         * \return Pointer to the EventGroup to chain calls
         */
        EventGroup& remove(const std::string& eventName);
        /**
         * \brief Enables a Trigger
         * \param eventName Name of the Trigger to enable
         * \return Pointer to the EventGroup to chain calls
         */
        EventGroup& trigger(const std::string& eventName, EventData data);
        /**
         * \brief Get the name of all Trigger contained in the EventGroup
         * \return A std::vector of std::string containing the name of all
         * Trigger contained in the EventGroup
         */
        std::vector<std::string> getEventsNames();
        /**
         * \brief Get all the Trigger contained in the EventGroup
         * \return A std::vector of Trigger pointers
         */
        std::vector<Event*> getEvents();
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
         * \brief Register a callback for when Trigger::register is called
         */
        void onRegister(const std::string& eventName, OnListenerChange callback);
        /**
         * \brief Register a callback for when Trigger::unRegister is called
         */
        void onUnregister(const std::string& eventName, OnListenerChange callback);
        vili::node getProfilerResults();
    };

    using EventGroupPtr = std::shared_ptr<EventGroup>;
} // namespace obe::Triggers