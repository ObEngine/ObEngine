#pragma once

#include <Audio/AudioManager.hpp>
#include <Config/Config.hpp>
#include <Debug/Logger.hpp>
#include <Engine/ResourceManager.hpp>
#include <Event/EventManager.hpp>
#include <Input/InputManager.hpp>
#include <Scene/Scene.hpp>
#include <Script/LuaState.hpp>
#include <System/Cursor.hpp>
#include <System/Plugin.hpp>
#include <System/Window.hpp>
#include <Time/FramerateManager.hpp>

namespace obe::bindings
{
    void index_core_bindings(sol::state_view state);
}

namespace obe::events
{
    namespace Game
    {
        struct Start
        {
            static constexpr std::string_view id = "Start";
        };

        struct Update
        {
            static constexpr std::string_view id = "Update";
            double dt;
        };

        struct End
        {
            static constexpr std::string_view id = "End";
        };

        struct Render
        {
            static constexpr std::string_view id = "Render";
        };
    } // namespace Game
} // namespace obe::events

namespace obe::engine
{
    class Engine
    {
    protected:
        bool m_initialized = false;
        std::vector<std::unique_ptr<system::Plugin>> m_plugins;
        std::unique_ptr<script::LuaState> m_lua;
        std::unique_ptr<scene::Scene> m_scene;
        std::unique_ptr<system::Cursor> m_cursor;
        std::unique_ptr<system::Window> m_window;
        debug::Logger::weak_type m_log;

        // Configuration
        vili::node m_arguments;

        // Managers
        audio::AudioManager m_audio {};
        config::ConfigurationManager m_config {};
        std::unique_ptr<ResourceManager> m_resources {};
        std::unique_ptr<input::InputManager> m_input {};
        std::unique_ptr<time::FramerateManager> m_framerate;
        std::unique_ptr<event::EventManager> m_events;
        event::EventNamespace* m_event_namespace;
        event::EventNamespace* m_user_event_namespace;

        // EventGroups
        event::EventGroupPtr e_game {};
        event::EventGroupPtr e_custom {};

        // Initialization
        void init_config();
        void init_logger() const;
        void init_script();
        void init_events();
        void init_input();
        void init_framerate();
        void init_resources();
        void init_window();
        void init_cursor();
        void init_plugins();
        void init_scene();

        // Main loop
        void handle_window_events() const;
        void update() const;
        void render() const;

        // Cleaning
        void clean() const;
        void purge();
        void deinit_plugins();

    public:
        Engine();
        ~Engine();

        Engine& operator=(Engine&&) = delete;

        void init(const vili::node& arguments);
        void run() const;

        /**
         * \rename{Audio}
         * \asproperty
         */
        audio::AudioManager& get_audio_manager();
        /**
         * \rename{Configuration}
         * \asproperty
         */
        config::ConfigurationManager& get_configuration_manager();
        /**
         * \rename{Resources}
         * \asproperty
         */
        ResourceManager& get_resource_manager();
        /**
         * \rename{Input}
         * \asproperty
         */
        input::InputManager& get_input_manager() const;
        /**
         * \rename{Framerate}
         * \asproperty
         */
        time::FramerateManager& get_framerate_manager() const;
        /**
         * \rename{Events}
         * \asproperty
         */
        event::EventManager& get_event_manager() const;

        /**
         * \rename{Scene}
         * \asproperty
         */
        scene::Scene& get_scene() const;
        /**
         * \rename{Cursor}
         * \asproperty
         */
        system::Cursor& get_cursor() const;
        /**
         * \rename{Window}
         * \asproperty
         */
        system::Window& get_window() const;
        /**
         * \nobind
         */
        script::LuaState& get_lua_state() const;
        /**
         * \nobind
         */
        debug::Logger get_logger() const;

        [[nodiscard]] const vili::node& get_arguments() const;

    };

    /**
    * \proxy{obe::engine::get_args}
    */
    sol::lua_value engine_get_args_proxy(const Engine* self);
} // namespace obe::engine
