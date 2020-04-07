#include <Engine/Engine.hpp>

#include <Utils/StringUtils.hpp>

#include "Graphics/Shapes.hpp"

int lua_exception_handler(lua_State* L,
    sol::optional<const std::exception&> maybe_exception, sol::string_view description)
{
    if (maybe_exception)
    {
        const std::exception& ex = *maybe_exception;
        obe::Debug::Log->error("<LuaError>[Exception] : {}", ex.what());
    }
    else
    {
        obe::Debug::Log->error("<LuaError>[Error] : {}", description);
    }
    return sol::stack::push(L, description);
}

namespace obe::Engine
{
    void Engine::initConfig()
    {
        m_config.load();
    }

    void Engine::initTriggers()
    {
        m_lua["__TRIGGERS"].get_or_create<sol::table>();
        m_triggers = std::make_unique<Triggers::TriggerManager>(m_lua);
        m_triggers->createNamespace("Event");
        t_game = m_triggers->createTriggerGroup("Event", "Game");

        t_game->add("Start").trigger("Start").add("End").add("Update").add("Render");
    }
    void Engine::initInput()
    {
        m_input = std::make_unique<Input::InputManager>();
        m_input->init(*m_triggers);
        m_input->configure(m_config.get().at("KeyBinding"));
        m_input->addContext("game");
    }

    void Engine::initFramerate()
    {
        m_framerate = std::make_unique<Time::FramerateManager>(*m_window);
        m_framerate->configure(m_config.get().at("GameConfig"));
    }

    void Engine::initScript()
    {
        m_lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table,
            sol::lib::package, sol::lib::os, sol::lib::coroutine, sol::lib::math,
            sol::lib::count, sol::lib::debug, sol::lib::io, sol::lib::bit32);

        m_lua.safe_script_file("Lib/Internal/LuaCore.lua"_fs);
        m_lua.safe_script_file("Lib/Internal/Environment.lua"_fs);
        m_lua.safe_script_file("Lib/Internal/ScriptInit.lua"_fs);
        m_lua.safe_script_file("Lib/Internal/Triggers.lua"_fs);

        Bindings::IndexAllBindings(m_lua);
        m_lua.safe_script_file("Lib/Internal/GameInit.lua"_fs);
        m_lua.set_exception_handler(lua_exception_handler);

        m_lua["Engine"] = this;
    }

    void Engine::initResources()
    {
        if (m_config.get().contains(vili::NodeType::ComplexNode, "GameConfig"))
        {
            vili::ComplexNode& gameConfig = m_config.get().at("GameConfig");
            if (gameConfig.contains(vili::NodeType::DataNode, "antiAliasing"))
            {
                m_resources.defaultAntiAliasing
                    = gameConfig.getDataNode("antiAliasing").get<bool>();
                Debug::Log->debug("<ResourceManager> AntiAliasing Default is {}",
                    m_resources.defaultAntiAliasing);
            }
        }
    }

    void Engine::initWindow()
    {
        m_window = std::make_unique<System::Window>(System::WindowContext::GameWindow);
    }

    void Engine::initCursor()
    {
        m_cursor = std::make_unique<System::Cursor>(*m_window, *m_triggers);
    }

    void Engine::initPlugins()
    {
        for (const System::MountablePath& mountedPath : System::Path::MountedPaths)
        {
            Debug::Log->info("<Bindings> Checking Plugins on Mounted Path : {0}",
                mountedPath.basePath);
            System::Path cPluginPath = System::Path(mountedPath.basePath).add("Plugins");
            if (Utils::File::directoryExists(cPluginPath.toString()))
            {
                for (const std::string& filename :
                    Utils::File::getFileList(cPluginPath.toString()))
                {
                    const std::string pluginPath = cPluginPath.add(filename).toString();
                    const std::string pluginName = Utils::String::split(filename, ".")[0];
                    m_plugins.emplace_back(
                        std::make_unique<System::Plugin>(pluginName, pluginPath));
                }
            }
        }
    }

    void Engine::initScene()
    {
        m_scene = std::make_unique<Scene::Scene>(*m_triggers, m_lua);
        m_scene->attachResourceManager(m_resources);
    }

    void Engine::initLogger() const
    {
        const unsigned int logLevel
            = m_config.get().at("Debug").getDataNode("logLevel").get<int>();
        const auto level = static_cast<spdlog::level::level_enum>(logLevel);
        if (m_config.get().contains("Debug")
            && m_config.get().at("Debug").contains("logLevel"))
            Debug::Log->set_level(level);
        Debug::Log->info("Log Level {}", logLevel);
    }

    void Engine::clean()
    {
        t_game->trigger("End");
        m_triggers->update();
        m_scene->clear();
        m_scene->update();
        Script::GameObjectDatabase::Clear();
        m_window->close();

        m_window.reset();
        m_cursor.reset();
        m_framerate.reset();
        m_input.reset();
        m_scene.reset();

        t_game.reset();
    }

    void Engine::handleWindowEvents()
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window->close();
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
            case sf::Event::JoystickButtonPressed:
            case sf::Event::JoystickButtonReleased:
            case sf::Event::JoystickMoved:
            case sf::Event::KeyReleased:
            case sf::Event::KeyPressed:
                m_input->requireRefresh();
                if (event.key.code == sf::Keyboard::Escape)
                    m_window->close();
                break;
            default:
                break;
            }
        }
    }

    Engine::Engine()
    {
        this->initConfig();
        this->initLogger();
        this->initScript();
        this->initTriggers();
        this->initInput();
        this->initWindow();
        this->initCursor();
        this->initFramerate();
        this->initPlugins();
        this->initResources();
        this->initScene();
    }

    void Engine::run()
    {

        m_lua.safe_script_file("boot.lua"_fs);
        m_window->create();
        m_lua["Game"]["Start"]();
        Graphics::Shapes::Rectangle rect;
        rect.setPosition(Transform::UnitVector(2, 1));
        rect.dbg();

        while (m_window->isOpen())
        {
            m_framerate->update();

            t_game->pushParameter("Update", "dt", m_framerate->getGameSpeed());
            t_game->trigger("Update");

            if (m_framerate->doRender())
                t_game->trigger("Render");

            this->update();
            this->render();
        }
        this->clean();
    }

    Audio::AudioManager& Engine::getAudioManager()
    {
        return m_audio;
    }

    Config::ConfigurationManager& Engine::getConfigurationManager()
    {
        return m_config;
    }

    ResourceManager& Engine::getResourceManager()
    {
        return m_resources;
    }

    Input::InputManager& Engine::getInputManager()
    {
        return *m_input;
    }

    Time::FramerateManager& Engine::getFramerateManager()
    {
        return *m_framerate;
    }

    Triggers::TriggerManager& Engine::getTriggerManager()
    {
        return *m_triggers;
    }

    Scene::Scene& Engine::getScene()
    {
        return *m_scene;
    }

    System::Cursor& Engine::getCursor()
    {
        return *m_cursor;
    }

    System::Window& Engine::getWindow()
    {
        return *m_window;
    }

    void Engine::update()
    {
        // Events
        this->handleWindowEvents();
        m_scene->update();
        m_triggers->update();
        m_input->update();
        m_cursor->update();
    }

    void Engine::render() const
    {
        if (m_framerate->doRender())
        {
            m_window->clear();
            m_scene->draw(m_window->getTarget());

            m_window->display();
        }
    }
}
