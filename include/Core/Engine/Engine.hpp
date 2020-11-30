#pragma once

#include "Entities/Entity.hpp"

#include <Audio/AudioManager.hpp>
#include <Config/Config.hpp>
#include <Engine/ResourceManager.hpp>
#include <Event/EventManager.hpp>
#include <Input/InputManager.hpp>
#include <Scene/Scene.hpp>
#include <System/Cursor.hpp>
#include <System/Plugin.hpp>
#include <System/Window.hpp>
#include <Time/FramerateManager.hpp>
#include <entt/entity/registry.hpp>
#include <sol/sol.hpp>

namespace obe::Bindings
{
    void IndexAllBindings(sol::state_view state);
}

namespace obe::Events::Game
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

namespace obe::Engine
{
    class Engine
    {
    protected:
        bool m_initialized = false;
        entt::registry m_registry;
        std::vector<std::unique_ptr<Entities::EntityBase>> m_entities;
        std::vector<std::unique_ptr<System::Plugin>> m_plugins;
        std::unique_ptr<sol::state> m_lua;
        std::unique_ptr<Scene::Scene> m_scene;
        std::unique_ptr<System::Cursor> m_cursor;
        std::unique_ptr<System::Window> m_window;

        // Managers
        Audio::AudioManager m_audio {};
        Config::ConfigurationManager m_config {};
        std::unique_ptr<ResourceManager> m_resources {};
        std::unique_ptr<Input::InputManager> m_input {};
        std::unique_ptr<Time::FramerateManager> m_framerate;
        std::unique_ptr<Event::EventManager> m_events;
        Event::EventNamespace* m_eventNamespace;

        // TriggerGroups
        Event::EventGroupPtr e_game {};

        // Initialization
        void initConfig();
        void initLogger() const;
        void initScript();
        void initEvents();
        void initInput();
        void initFramerate();
        void initResources();
        void initWindow();
        void initCursor();
        void initPlugins();
        void initScene();

        // Main loop
        void handleWindowEvents() const;
        void update() const;
        void render() const;

        // Cleaning
        void clean() const;
        void purge();

    public:
        Engine();
        ~Engine();

        void init();
        void run() const;

        /**
         * \bind{Audio}
         * \asproperty
         */
        Audio::AudioManager& getAudioManager();
        /**
         * \bind{Configuration}
         * \asproperty
         */
        Config::ConfigurationManager& getConfigurationManager();
        /**
         * \bind{Resources}
         * \asproperty
         */
        ResourceManager& getResourceManager();
        /**
         * \bind{Input}
         * \asproperty
         */
        Input::InputManager& getInputManager() const;
        /**
         * \bind{Framerate}
         * \asproperty
         */
        Time::FramerateManager& getFramerateManager() const;
        /**
         * \bind{Events}
         * \asproperty
         */
        Event::EventManager& getEventManager() const;

        /**
         * \bind{Scene}
         * \asproperty
         */
        Scene::Scene& getScene() const;
        /**
         * \bind{Cursor}
         * \asproperty
         */
        System::Cursor& getCursor() const;
        /**
         * \bind{Window}
         * \asproperty
         */
        System::Window& getWindow() const;
    };
}