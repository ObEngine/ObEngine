#include <fstream>

#include <Engine/Engine.hpp>
#include <Engine/Exceptions.hpp>
#include <Utils/FileUtils.hpp>

int lua_exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception,
    sol::string_view description)
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

    void Engine::initInput()
    {
        m_input = std::make_unique<Input::InputManager>(*m_eventNamespace);
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
        m_lua = std::make_unique<Script::LuaState>();
        m_lua->open_libraries(sol::lib::base, sol::lib::string, sol::lib::table, sol::lib::package,
            sol::lib::os, sol::lib::coroutine, sol::lib::math, sol::lib::count, sol::lib::debug,
            sol::lib::io, sol::lib::bit32);

        m_lua->safe_script("LuaCore = {}");
        m_lua->safe_script_file("obe://Lib/Internal/ScriptInit.lua"_fs);
        m_lua->safe_script_file("obe://Lib/Internal/Events.lua"_fs);

        Bindings::IndexAllBindings(*m_lua);

        m_lua->loadConfig(m_config.at("Script").at("Lua"));

        m_lua->safe_script_file("obe://Lib/Internal/Helpers.lua"_fs);
        m_lua->safe_script_file("obe://Lib/Internal/GameInit.lua"_fs);
        m_lua->safe_script_file("obe://Lib/Internal/Logger.lua"_fs);
        m_lua->set_exception_handler(&lua_exception_handler);
        m_lua->safe_script("collectgarbage(\"generational\");");

        (*m_lua)["Engine"] = this;
    }

    void Engine::initEvents()
    {
        m_events = std::make_unique<Event::EventManager>();
        m_eventNamespace = &m_events->createNamespace("Event");
        e_game = m_eventNamespace->createGroup("Game");

        e_game->add<Events::Game::Start>();
        e_game->add<Events::Game::End>();
        e_game->add<Events::Game::Update>();
        e_game->add<Events::Game::Render>();

        e_game->trigger(Events::Game::Start {});
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
        m_cursor = std::make_unique<System::Cursor>(*m_window, *m_eventNamespace);
    }

    void Engine::initPlugins()
    {
        for (const auto& mountedPath : System::MountablePath::Paths())
        {
            Debug::Log->info(
                "<Bindings> Checking Plugins on Mounted Path : {0}", mountedPath->basePath);
            System::Path cPluginPath = System::Path(mountedPath->basePath).add("Plugins");
            if (Utils::File::directoryExists(cPluginPath.toString()))
            {
                for (const std::string& filename : Utils::File::getFileList(cPluginPath.toString()))
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
        m_scene = std::make_unique<Scene::Scene>(*m_eventNamespace, *m_lua);
        m_scene->attachResourceManager(*m_resources);
    }

    void Engine::initLogger() const
    {
        if (m_config.contains("Debug"))
        {
            vili::node debug = m_config.at("Debug");
            if (debug.contains("Logging"))
            {
                vili::node logging = debug.at("Logging");
                if (logging.contains("level"))
                {
                    const unsigned int logLevel = logging.at("level");
                    const auto level = static_cast<spdlog::level::level_enum>(logLevel);
                    Debug::Log->set_level(level);
                    Debug::Log->info("Log Level {}", logLevel);
                }
            }
        }
    }

    void Engine::clean() const
    {
        if (e_game)
        {
            e_game->trigger(Events::Game::End {});
        }
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
        Debug::Log->debug("Cleaning Window");
        m_window.reset();
        Debug::Log->debug("Cleaning Cursor");
        m_cursor.reset();
        Debug::Log->debug("Cleaning Framerate");
        m_framerate.reset();
        Debug::Log->debug("Cleaning Scene");
        m_scene.reset();
        Debug::Log->debug("Running Lua State Garbage Collection");
        if (m_lua)
        {
            m_lua->collect_garbage();
            m_lua->collect_garbage();
        }
        Debug::Log->debug("Cleaning ResourceManager");
        m_resources.reset();
        Debug::Log->debug("Cleaning Game Events");
        e_game.reset();
        Debug::Log->debug("Cleaning InputManager");
        m_input.reset();
        Debug::Log->debug("Cleaning Events");
        if (m_events)
        {
            m_events->clear();
            m_events->update();
        }
        m_events.reset();
        Debug::Log->debug("Cleaning Lua State");
        m_lua.reset();
    }

    void Engine::handleWindowEvents() const
    {
        sf::Event event;
        m_input->getInput("MouseWheelUp").setMouseWheelDelta(0);
        m_input->getInput("MouseWheelDown").setMouseWheelDelta(0);
        m_input->getInput("MouseWheelLeft").setMouseWheelDelta(0);
        m_input->getInput("MouseWheelRight").setMouseWheelDelta(0);
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    if (event.mouseWheelScroll.delta < 0)
                    {
                        m_input->getInput("MouseWheelUp")
                            .setMouseWheelDelta(event.mouseWheelScroll.delta);
                    }
                    else if (event.mouseWheelScroll.delta > 0)
                    {
                        m_input->getInput("MouseWheelDown")
                            .setMouseWheelDelta(event.mouseWheelScroll.delta);
                    }
                }
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                {
                    if (event.mouseWheelScroll.delta < 0)
                    {
                        m_input->getInput("MouseWheelLeft")
                            .setMouseWheelDelta(event.mouseWheelScroll.delta);
                    }
                    else if (event.mouseWheelScroll.delta > 0)
                    {
                        m_input->getInput("MouseWheelRight")
                            .setMouseWheelDelta(event.mouseWheelScroll.delta);
                    }
                }
            }
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window->close();
                break;
            case sf::Event::Resized:
                m_window->setWindowSize(event.size.width, event.size.height);
                break;
            case sf::Event::JoystickConnected:
                [[fallthrough]];
            case sf::Event::JoystickDisconnected:
                m_input->initializeGamepads();
            case sf::Event::MouseWheelScrolled:
                [[fallthrough]];
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
        catch (BaseException& e)
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
        this->initEvents();
        this->initInput();
        this->initWindow();
        this->initCursor();
        this->initFramerate();
        this->initPlugins();
        this->initResources();
        this->initScene();
        m_initialized = true;
    }

    void Engine::run() const
    {
        if (!m_initialized)
            throw Exceptions::UnitializedEngine(EXC_INFO);

        const std::string bootScript = "*://boot.lua"_fs;
        if (bootScript.empty())
            throw Exceptions::BootScriptMissing(System::MountablePath::StringPaths(), EXC_INFO);
        const sol::protected_function_result loadResult = m_lua->safe_script_file(bootScript);

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
            throw Exceptions::BootScriptExecutionError("Game.Start", errObj.what(), EXC_INFO);
        }

        m_framerate->start();
        vili::array dts;
        Time::TimeUnit start = Time::epoch();
        while (m_window->isOpen())
        {
            m_framerate->update();

            if (m_framerate->doUpdate())
            {
                dts.push_back(m_framerate->getGameSpeed());
                e_game->trigger(Events::Game::Update { m_framerate->getGameSpeed() });
                this->update();
            }

            if (m_framerate->doRender())
            {
                e_game->trigger(Events::Game::Render {});
                this->render();
                m_framerate->reset();
            }
            else
            {
                // m_lua->collect_garbage();
                // m_lua->collect_garbage();
            }
        }
        Time::TimeUnit totalTime = Time::epoch() - start;
        double dtSum = 0;
        for (auto dt : dts)
        {
            dtSum += dt.as<double>();
        }
        Debug::Log->info("Execution completed with {} ticks in {} seconds (dt sum: {})", dts.size(),
            totalTime, dtSum);
        vili::node profiler = m_events->dumpProfilerResults();
        profiler.emplace("dts", dts);
        std::ofstream profilerOutput;
        profilerOutput.open("profiler.vili");
        std::string dump = profiler.dump();
        profilerOutput.write(dump.data(), dump.size());
        profilerOutput.close();
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

    Event::EventManager& Engine::getEventManager() const
    {
        return *m_events;
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
        m_events->update();
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
