#pragma once

#include <Audio/AudioManager.hpp>
#include <Config/Config.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Input/InputManager.hpp>
#include <Scene/Scene.hpp>
#include <System/Cursor.hpp>
#include <System/Plugin.hpp>
#include <System/Window.hpp>
#include <Time/FramerateManager.hpp>
#include <Triggers/TriggerManager.hpp>
#include <sol/sol.hpp>
#include <spdlog/logger.h>
#include <vili/ViliParser.hpp>

namespace obe::Engine
{
    class Engine
    {
    protected:
        sol::state m_lua;
        std::vector<std::unique_ptr<System::Plugin>> m_plugins;
        Scene::Scene m_scene;
        System::Cursor m_cursor;
        System::Window m_window;

        // Managers
        Audio::AudioManager m_audio;
        Config::ConfigurationManager m_config;
        Graphics::ResourceManager m_resources;
        Input::InputManager m_input;
        Time::FramerateManager m_framerate;
        Triggers::TriggerManager m_triggers;

        // TriggerGroups
        Triggers::TriggerGroupPtr t_game;

        // Initialisation
        void initConfig();
        void initLogger();
        void initTriggers();
        void initInput();
        void initFramerate();
        void initScript();
        void initResources();
        void initWindow();
        void initPlugins();

        // Main loop
        void clean();
        void handleWindowEvents();
        void update();
        void render();

    public:
        Engine();
        void run();
    };
}