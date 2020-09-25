#pragma once

#include <utility>

#include <sol/sol.hpp>

#include <Debug/Logger.hpp>
#include <Event/EventListener.hpp>
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

    using EventProfiler = std::unordered_map<std::string, CallbackProfiler>;
    using OnListenerChange = std::function<void(const EventListener&)>;

    /**
     * \brief A Class that does represents a triggerable event
     */
    class Event
    {
    private:
        std::string m_name;
        std::string m_identifier;
        std::vector<EventListener> m_listeners;
        bool m_triggered = false;
        bool m_enabled = false;
        std::function<void(const EventListener&)> m_onRegisterCallback;
        EventProfiler m_profiler;
        friend class EventGroup;
        friend class EventManager;

    protected:
        /**
         * \brief Event callbacks
         */
        void execute(const EventData& event);
        void onRegister(OnListenerChange callback);
        void onUnregister(OnListenerChange callback);

    public:
        /**
         * \brief Creates a new Trigger
         * \param parent Pointer to the parent TriggerGroup
         * \param name Name of the Trigger
         * \param startState State of the Trigger when created (enabled /
         *        disabled)
         */
        explicit Event(
            const EventGroup& parent, const std::string& name, bool startState = false);
        /**
         * \brief Get the State of the Event (enabled / disabled)
         * \return true if the Trigger is enabled, false otherwise
         */
        bool getState() const;
        /**
         * \brief Get the name of the Event
         * \return A std::string containing the name of the Event
         */
        [[nodiscard]] std::string getName() const;
        /**
         * \brief Get the identifier of the Event
         * \return A std::string containing the name of the Event
         */
        [[nodiscard]] std::string getName() const;
        /**
         * \brief Registers a Lua State that will be triggered
         * \param environment Lua Environment to register
         * \param callback Name of the callback to register
         * \param active Pointer to the boolean that indicate if an
         *        environment is active or not
         */
        void addListener(EventListener listener);
        /**
         * \brief Removes an environment from Trigger Execution
         * \param environment Lua Environment to unregister
         */
        void removeListener(const std::string& id);
    };
} // namespace obe::Event
