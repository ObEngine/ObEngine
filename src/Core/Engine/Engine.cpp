#include <Engine/Engine.hpp>
#include <Engine/Exceptions.hpp>
#include <Utils/StringUtils.hpp>

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
        (*m_lua)["__TRIGGERS"].get_or_create<sol::table>();
        m_triggers = std::make_unique<Triggers::TriggerManager>(*m_lua);
        m_triggers->createNamespace("Event");
        t_game = m_triggers->createTriggerGroup("Event", "Game");

        t_game->add("Start").trigger("Start").add("End").add("Update").add("Render");
    }
    void Engine::initInput()
    {
        m_input = std::make_unique<Input::InputManager>();
        m_input->init(*m_triggers);
        if (m_config.contains("Input"))
        {
            m_input->configure(m_config.at("Input"));
        }
        m_input->addContext("game");
    }

    void Engine::initFramerate()
    {
        m_framerate = std::make_unique<Time::FramerateManager>(*m_window);
        m_framerate->configure(m_config.at("Framerate"));
    }

    void Engine::initScript()
    {
        m_lua = std::make_unique<sol::state>();
        m_lua->open_libraries(sol::lib::base, sol::lib::string, sol::lib::table,
            sol::lib::package, sol::lib::os, sol::lib::coroutine, sol::lib::math,
            sol::lib::count, sol::lib::debug, sol::lib::io, sol::lib::bit32);

        m_lua->safe_script("LuaCore = {}");
        m_lua->safe_script_file("Lib/Internal/ScriptInit.lua"_fs);
        m_lua->safe_script_file("Lib/Internal/Triggers.lua"_fs);

        Bindings::IndexAllBindings(*m_lua);
        m_lua->safe_script_file("Lib/Internal/Searcher.lua"_fs);
        m_lua->safe_script_file("Lib/Internal/GameInit.lua"_fs);
        m_lua->safe_script_file("Lib/Internal/Logger.lua"_fs);
        m_lua->set_exception_handler(&lua_exception_handler);

        (*m_lua)["Engine"] = this;
    }

    void Engine::initResources()
    {
        m_resources = std::make_unique<ResourceManager>();
        if (m_config.contains("GameConfig"))
        {
            const vili::node& gameConfig = m_config.at("GameConfig");
            if (gameConfig.contains("antiAliasing"))
            {
                m_resources->defaultAntiAliasing = gameConfig.at("antiAliasing");
                Debug::Log->debug("<ResourceManager> AntiAliasing Default is {}",
                    m_resources->defaultAntiAliasing);
            }
        }
    }

    void Engine::initWindow()
    {
        vili::node windowConfig = m_config.at("Window").at("Game");
        Debug::Log->debug("<Engine> Window configuration : {}", windowConfig.dump());
        m_window = std::make_unique<System::Window>(windowConfig);
    }

    void Engine::initCursor()
    {
        m_cursor = std::make_unique<System::Cursor>(*m_window, *m_triggers);
    }

    void Engine::initPlugins()
    {
        for (const System::MountablePath& mountedPath : System::MountablePath::Paths())
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
        m_scene = std::make_unique<Scene::Scene>(*m_triggers, *m_lua);
        m_scene->attachResourceManager(*m_resources);
    }

    void Engine::initLogger() const
    {
        if (m_config.contains("Debug"))
        {
            vili::node debug = m_config.at("Debug");
            if (debug.contains("logLevel"))
            {
                const unsigned int logLevel = debug.at("logLevel");
                const auto level = static_cast<spdlog::level::level_enum>(logLevel);
                Debug::Log->set_level(level);
                Debug::Log->info("Log Level {}", logLevel);
            }
        }
    }

    void Engine::clean() const
    {
        if (t_game)
        {
            t_game->trigger("End");
        }
        if (m_triggers)
            m_triggers->update();
        if (m_scene)
        {
            m_scene->clear();
            m_scene->update();
        }
        Script::GameObjectDatabase::Clear();
        if (m_window)
            m_window->close();

        // m_lua->clear();
    }

    void Engine::purge()
    {
        m_window.reset();
        m_cursor.reset();
        m_framerate.reset();
        m_scene.reset();
        if (m_lua)
        {
            m_lua->collect_garbage();
            m_lua->collect_garbage();
        }
        m_resources.reset();
        t_game.reset();
        m_input.reset();
        m_triggers.reset();
        m_lua.reset();
    }

    void Engine::handleWindowEvents() const
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
                [[fallthrough]];
            case sf::Event::MouseButtonReleased:
                [[fallthrough]];
            case sf::Event::JoystickButtonPressed:
                [[fallthrough]];
            case sf::Event::JoystickButtonReleased:
                [[fallthrough]];
            case sf::Event::JoystickMoved:
                [[fallthrough]];
            case sf::Event::KeyReleased:
                [[fallthrough]];
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
    }

    Engine::~Engine()
    {
        try
        {
            this->clean();
        }
        catch (Exception& e)
        {
            Debug::Log->error("Failed to properly clean the engine :\n{}", e.what());
        }
        this->purge();
        Debug::Log->debug("Engine has been correctly cleaned");
    }

    void Engine::init()
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
        m_initialized = true;
    }

    void Engine::run()
    {
        if (!m_initialized)
            throw Exceptions::UnitializedEngine(EXC_INFO);

        const std::string bootScript = "boot.lua"_fs;
        if (bootScript.empty())
            throw Exceptions::BootScriptMissing(
                System::MountablePath::StringPaths(), EXC_INFO);
        const sol::protected_function_result loadResult
            = m_lua->safe_script_file(bootScript);

        if (!loadResult.valid())
        {
            const auto errObj = loadResult.get<sol::error>();
            throw Exceptions::BootScriptLoadingError(errObj.what(), EXC_INFO);
        }
        m_window->create();
        const sol::protected_function bootFunction
            = (*m_lua)["Game"]["Start"].get<sol::protected_function>();

        const sol::protected_function_result bootResult = bootFunction.call();
        if (!bootResult.valid())
        {
            const auto errObj = bootResult.get<sol::error>();
            throw Exceptions::BootScriptExecutionError(
                "Game.Start", errObj.what(), EXC_INFO);
        }

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
        return *m_resources;
    }

    Input::InputManager& Engine::getInputManager() const
    {
        return *m_input;
    }

    Time::FramerateManager& Engine::getFramerateManager() const
    {
        return *m_framerate;
    }

    Triggers::TriggerManager& Engine::getTriggerManager() const
    {
        return *m_triggers;
    }

    Scene::Scene& Engine::getScene() const
    {
        return *m_scene;
    }

    System::Cursor& Engine::getCursor() const
    {
        return *m_cursor;
    }

    System::Window& Engine::getWindow() const
    {
        return *m_window;
    }

    void Engine::update() const
    {
        // Events
        this->handleWindowEvents();
        m_scene->update();
        m_triggers->update();
        m_input->update();
        m_cursor->update();
    }

    void Engine::render()
    {
        m_lua->collect_garbage();
        if (m_framerate->doRender())
        {
            m_window->clear();
            m_scene->draw(m_window->getTarget());

            m_window->display();
        }
    }
}
