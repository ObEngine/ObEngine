#pragma once

#include <Audio/AudioManager.hpp>
#include <Config/Config.hpp>
#include <Engine/ResourceManager.hpp>
#include <Input/InputManager.hpp>
#include <Scene/Scene.hpp>
#include <System/Cursor.hpp>
#include <System/Plugin.hpp>
#include <System/Window.hpp>
#include <Time/FramerateManager.hpp>
#include <Triggers/TriggerManager.hpp>
#include <sol/sol.hpp>

namespace obe::Bindings
{
    void IndexAllBindings(sol::state_view state);
}

namespace obe::Engine
{
    class Engine
    {
    protected:
        sol::state m_lua;
        std::vector<std::unique_ptr<System::Plugin>> m_plugins;
        std::unique_ptr<Scene::Scene> m_scene;
        std::unique_ptr<System::Cursor> m_cursor;
        std::unique_ptr<System::Window> m_window;

        // Managers
        Audio::AudioManager m_audio {};
        Config::ConfigurationManager m_config {};
        ResourceManager m_resources {};
        Input::InputManager m_input {};
        std::unique_ptr<Time::FramerateManager> m_framerate;
        Triggers::TriggerManager m_triggers {};

        // TriggerGroups
        Triggers::TriggerGroupPtr t_game {};

        // Initialization
        void initConfig();
        void initLogger() const;
        void initTriggers();
        void initInput();
        void initFramerate();
        void initScript();
        void initResources();
        void initWindow();
        void initCursor();
        void initPlugins();
        void initScene();

        // Main loop
        void clean();
        void handleWindowEvents();
        void update();
        void render() const;

    public:
        Engine();
        void run();
    };
}