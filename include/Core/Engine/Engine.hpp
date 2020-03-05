#pragma once

#include <Audio/AudioManager.hpp>
#include <Graphics/ResourceManager.hpp>
#include <Input/InputManager.hpp>
#include <Scene/Scene.hpp>
#include <System/Cursor.hpp>
#include <System/Plugin.hpp>
#include <Time/FramerateManager.hpp>
#include <Triggers/TriggerManager.hpp>
#include <sol/sol.hpp>
#include <spdlog/logger.h>
#include <vili/ViliParser.hpp>

namespace obe::Engine
{
    class Engine
    {
    private:
        vili::ViliParser m_configuration;
        std::shared_ptr<spdlog::logger> m_logger;
        sol::state m_lua;
        std::vector<std::unique_ptr<System::Plugin>> m_plugins;
        Scene::Scene m_scene;
        System::Cursor m_cursor;

        // Managers
        Audio::AudioManager m_audio;
        Graphics::ResourceManager m_resources;
        Input::InputManager m_input;
        Time::FramerateManager m_framerate;
        Triggers::TriggerManager m_trigger;
    };
}