#include <Engine/Engine.hpp>

#include <Utils/StringUtils.hpp>

namespace obe::Engine
{
    void Engine::initConfig()
    {
        m_config.load();
    }

    void Engine::initTriggers()
    {
        t_game = m_triggers.createTriggerGroup("Global", "Game");

        t_game->addTrigger("Start")
            ->trigger("Start")
            ->addTrigger("End")
            ->addTrigger("Update")
            ->addTrigger("Render");
    }
    void Engine::initInput()
    {
        m_input.init(m_triggers);
        m_input.configure(m_config.get().at("KeyBinding"));
        m_input.addContext("game");
    }

    void Engine::initFramerate()
    {
        m_framerate.configure(m_config.get().at("GameConfig"));
    }

    void Engine::initScript()
    {
        m_lua.open_libraries(
            sol::lib::base, sol::lib::io, sol::lib::string, sol::lib::table);
        m_lua.script_file("Lib/Internal/GameInit.lua"_fs);
        m_lua.script_file("boot.lua"_fs);

        m_lua["loadScene"] = [&](const std::string& path) { m_scene.loadFromFile(path); };
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
        m_window.init(System::WindowContext::GameWindow);
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

    void Engine::initLogger()
    {
        const unsigned int logLevel
            = m_config.get().at("Debug").getDataNode("logLevel").get<int>();
        const spdlog::level::level_enum lvle
            = static_cast<spdlog::level::level_enum>(logLevel);
        if (m_config.get().contains("Debug")
            && m_config.get().at("Debug").contains("logLevel"))
            Debug::Log->set_level(lvle);
        Debug::Log->info("Log Level {}", logLevel);
    }

    void Engine::clean()
    {
        t_game->trigger("End");
        m_triggers.update();
        m_scene.clear();
        m_scene.update();
        Script::GameObjectDatabase::Clear();
        m_window.close();
    }

    void Engine::handleWindowEvents()
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
            case sf::Event::JoystickButtonPressed:
            case sf::Event::JoystickButtonReleased:
            case sf::Event::JoystickMoved:
            case sf::Event::KeyReleased:
            case sf::Event::KeyPressed:
                m_input.requireRefresh();
                if (event.key.code == sf::Keyboard::Escape)
                    m_window.close();
                break;
            }
        }
    }

    Engine::Engine()
        : m_cursor(m_window)
    {
        this->initConfig();
        this->initLogger();
        this->initTriggers();
        this->initFramerate();
        this->initInput();
        this->initScript();
        this->initWindow();
        this->initPlugins();
    }

    void Engine::run()
    {
        m_window.create();
        m_lua["Game"]["Start"]();

        while (m_window.isOpen())
        {
            m_framerate.update();

            t_game->pushParameter("Update", "dt", m_framerate.getGameSpeed());
            t_game->trigger("Update");

            if (m_framerate.doRender())
                t_game->trigger("Render");

            this->update();
            this->render();
        }
        this->clean();
    }

    void Engine::update()
    {
        // Events
        this->handleWindowEvents();
        m_scene.update();
        m_triggers.update();
        m_input.update();
        m_cursor.update();
    }

    void Engine::render()
    {
        if (m_framerate.doRender())
        {
            m_window.clear();
            m_scene.draw(m_window.getTarget());

            m_window.display();
        }
    }
}
