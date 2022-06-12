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

namespace obe::Bindings
{
    void IndexCoreBindings(sol::state_view state);
}

namespace obe::events::game
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

}

namespace obe::engine
{
    class Engine
    {
    protected:
        bool m_initialized = false;
        std::vector<std::unique_ptr<System::Plugin>> m_plugins;
        std::unique_ptr<Script::LuaState> m_lua;
        std::unique_ptr<Scene::Scene> m_scene;
        std::unique_ptr<System::Cursor> m_cursor;
        std::unique_ptr<System::Window> m_window;
        debug::Logger::weak_type m_log;

        // Managers
        audio::AudioManager m_audio {};
        config::ConfigurationManager m_config {};
        std::unique_ptr<ResourceManager> m_resources {};
        std::unique_ptr<Input::InputManager> m_input {};
        std::unique_ptr<Time::FramerateManager> m_framerate;
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
        void deinit_plugins() const;

    public:
        Engine();
        ~Engine();

        Engine& operator=(Engine&&) = delete;

        void init();
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
        Input::InputManager& get_input_manager() const;
        /**
         * \rename{Framerate}
         * \asproperty
         */
        Time::FramerateManager& get_framerate_manager() const;
        /**
         * \rename{Events}
         * \asproperty
         */
        event::EventManager& get_event_manager() const;

        /**
         * \rename{Scene}
         * \asproperty
         */
        Scene::Scene& get_scene() const;
        /**
         * \rename{Cursor}
         * \asproperty
         */
        System::Cursor& get_cursor() const;
        /**
         * \rename{Window}
         * \asproperty
         */
        System::Window& get_window() const;
        /**
         * \nobind
         */
        Script::LuaState& get_lua_state() const;
        /**
         * \nobind
         */
        debug::Logger get_logger() const;
    };
}
