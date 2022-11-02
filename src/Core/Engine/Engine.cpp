#include <fstream>

#include <Engine/Engine.hpp>
#include <Engine/Exceptions.hpp>
#include <Input/InputSourceMouse.hpp>
#include <Script/LuaHelpers.hpp>
#include <Utils/FileUtils.hpp>


int lua_exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception,
    sol::string_view description)
{
    if (maybe_exception)
    {
        const std::exception& ex = *maybe_exception;
        obe::debug::Log->error("<LuaError>[Exception] : {}", ex.what());
    }
    else
    {
        obe::debug::Log->error("<LuaError>[Error] : {}", description);
    }
    return sol::stack::push(L, description);
}

namespace obe::engine
{
    void Engine::init_config()
    {
        m_config.load();
    }

    void Engine::init_input()
    {
        m_input = std::make_unique<input::InputManager>(*m_event_namespace);
        if (m_config.contains("Input"))
        {
            m_input->configure(m_config.at("Input"));
        }
        m_input->add_context("game");
    }

    void Engine::init_framerate()
    {
        m_framerate = std::make_unique<time::FramerateManager>(*m_window);
        m_framerate->configure(m_config.at("Framerate"));
    }

    void Engine::init_script()
    {
        m_lua = std::make_unique<script::LuaState>();
        m_lua->open_libraries(sol::lib::base, sol::lib::string, sol::lib::table, sol::lib::package,
            sol::lib::os, sol::lib::coroutine, sol::lib::math, sol::lib::count, sol::lib::debug,
            sol::lib::io, sol::lib::bit32);
        (*m_lua)["__ENV_ID"] = "[Global Environment]";
        // Table shared across all environments, for easy value sharing
        (*m_lua)["Global"] = sol::new_table();

        (*m_lua)["Helpers"] = sol::new_table();
        for (const auto& [helper_name, helper] : script::Helpers::make_all_helpers(*m_lua))
        {
            (*m_lua)["Helpers"][helper_name] = helper;
        }

        this->init_plugins();

        bindings::index_core_bindings(*m_lua);

        m_lua->load_config(m_config.at("Script").at("Lua"));

        m_lua->safe_script_file("obe://Lib/Internal/Helpers.lua"_fs);
        m_lua->safe_script_file("obe://Lib/Internal/Events.lua"_fs);
        m_lua->safe_script_file("obe://Lib/Internal/GameInit.lua"_fs);
        m_lua->safe_script_file("obe://Lib/Internal/Logger.lua"_fs);
        m_lua->set_exception_handler(&lua_exception_handler);
        m_lua->safe_script("collectgarbage(\"generational\");");

        (*m_lua)["Engine"] = this;
    }

    void Engine::init_events()
    {
        m_events = std::make_unique<event::EventManager>();
        m_event_namespace = &m_events->create_namespace("Event");
        m_user_event_namespace = &m_events->create_namespace("UserEvent");
        m_user_event_namespace->set_joinable(true);

        e_game = m_event_namespace->create_group("Game");
        e_game->add<events::Game::Start>();
        e_game->add<events::Game::End>();
        e_game->add<events::Game::Update>();
        e_game->add<events::Game::Render>();

        e_custom = m_user_event_namespace->create_group("Custom");
        e_custom->set_joinable(true);

        e_game->trigger(events::Game::Start {});
    }

    void Engine::init_resources()
    {
        m_resources = std::make_unique<ResourceManager>();
        if (m_config.contains("GameConfig"))
        {
            const vili::node& game_config = m_config.at("GameConfig");
            if (game_config.contains("antiAliasing"))
            {
                m_resources->default_anti_aliasing = game_config.at("antiAliasing");
                debug::Log->debug("<ResourceManager> AntiAliasing Default is {}",
                    m_resources->default_anti_aliasing);
            }
        }
    }

    void Engine::init_window()
    {
        vili::node window_config = m_config.at("Window").at("Game");
        debug::Log->debug("<Engine> Window configuration : {}", window_config.dump());
        m_window = std::make_unique<system::Window>(window_config);
    }

    void Engine::init_cursor()
    {
        m_cursor = std::make_unique<system::Cursor>(*m_window, *m_event_namespace);
    }

    void Engine::init_plugins()
    {
        debug::Log->info("<Bindings> Checking Plugins on Mounted Path : {0}",
            system::MountablePath::from_prefix("cwd").base_path);
        system::Path plugin_path_base
            = system::Path(system::MountablePath::from_prefix("cwd").base_path).add("Plugins");
        if (utils::file::directory_exists(plugin_path_base.to_string()))
        {
            for (const std::string& filename :
                utils::file::get_file_list(plugin_path_base.to_string()))
            {
                const std::string plugin_path = plugin_path_base.add(filename).to_string();
                const std::string plugin_name = utils::string::split(filename, ".")[0];
                auto plugin = std::make_unique<system::Plugin>(plugin_name, plugin_path);
                if (plugin->is_valid())
                {
                    m_plugins.emplace_back(std::move(plugin));
                }
            }
        }
        for (const auto& plugin : m_plugins)
        {
            plugin->on_init(*this);
        }
    }

    void Engine::init_scene()
    {
        m_scene = std::make_unique<scene::Scene>(*m_event_namespace, *m_lua);
        m_scene->attach_resource_manager(*m_resources);
    }

    void Engine::init_logger() const
    {
        if (m_config.contains("Debug"))
        {
            vili::node debug = m_config.at("Debug");
            if (debug.contains("Logging"))
            {
                vili::node logging = debug.at("Logging");
                if (logging.contains("level"))
                {
                    std::string log_level_config_entry = logging.at("level");
                    const debug::LogLevel log_level
                        = debug::LogLevelMeta::from_string(log_level_config_entry);
                    const auto level = static_cast<spdlog::level::level_enum>(log_level);
                    debug::Log->set_level(level);
                    debug::Log->info("Log Level {}", log_level_config_entry);
                }
            }
        }
    }

    void Engine::clean() const
    {
        if (e_game)
        {
            e_game->trigger(events::Game::End {});
        }
        if (m_scene)
        {
            m_scene->clear();
            m_scene->update();
        }
        script::GameObjectDatabase::clear();
        if (m_window)
            m_window->close();

        // m_lua->clear();
    }

    void Engine::purge()
    {
        debug::Log->debug("Cleaning Window");
        m_window.reset();
        debug::Log->debug("Cleaning Cursor");
        m_cursor.reset();
        debug::Log->debug("Cleaning Framerate");
        m_framerate.reset();
        debug::Log->debug("Cleaning Scene");
        m_scene.reset();
        debug::Log->debug("Running Lua State Garbage Collection");
        if (m_lua)
        {
            m_lua->collect_garbage();
            m_lua->collect_garbage();
        }
        debug::Log->debug("Cleaning ResourceManager");
        m_resources.reset();
        debug::Log->debug("Cleaning Game Events");
        e_game.reset();
        e_custom.reset();
        debug::Log->debug("Cleaning InputManager");
        m_input.reset();
        debug::Log->debug("Cleaning Events");
        if (m_events)
        {
            m_events->clear();
            m_events->update();
        }
        m_events.reset();
        debug::Log->debug("Cleaning Lua State");
        m_lua.reset();
    }

    void Engine::deinit_plugins()
    {
        for (const auto& plugin : m_plugins)
        {
            plugin->on_exit(*this);
        }
    }

    void Engine::handle_window_events() const
    {
        sf::Event event;
        input::InputSourceMouseWheelScroll* mouse_wheel_scroll_down
            = static_cast<input::InputSourceMouseWheelScroll*>(
                &m_input->get_input_source("MouseWheelScrollDown"));
        input::InputSourceMouseWheelScroll* mouse_wheel_scroll_up
            = static_cast<input::InputSourceMouseWheelScroll*>(
                &m_input->get_input_source("MouseWheelScrollUp"));
        input::InputSourceMouseWheelScroll* mouse_wheel_scroll_left
            = static_cast<input::InputSourceMouseWheelScroll*>(
                &m_input->get_input_source("MouseWheelScrollLeft"));
        input::InputSourceMouseWheelScroll* mouse_wheel_scroll_right
            = static_cast<input::InputSourceMouseWheelScroll*>(
                &m_input->get_input_source("MouseWheelScrollRight"));

        mouse_wheel_scroll_down->m_delta = 0;
        mouse_wheel_scroll_up->m_delta = 0;
        mouse_wheel_scroll_left->m_delta = 0;
        mouse_wheel_scroll_right->m_delta = 0;

        while (m_window->poll_event(event))
        {
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    if (event.mouseWheelScroll.delta < 0)
                    {
                        mouse_wheel_scroll_up->m_delta = event.mouseWheelScroll.delta;
                    }
                    else if (event.mouseWheelScroll.delta > 0)
                    {
                        mouse_wheel_scroll_down->m_delta = event.mouseWheelScroll.delta;
                    }
                }
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                {
                    if (event.mouseWheelScroll.delta < 0)
                    {
                        mouse_wheel_scroll_left->m_delta = event.mouseWheelScroll.delta;
                    }
                    else if (event.mouseWheelScroll.delta > 0)
                    {
                        mouse_wheel_scroll_right->m_delta = event.mouseWheelScroll.delta;
                    }
                }
            }
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window->close();
                break;
            case sf::Event::Resized:
                m_window->set_window_size(event.size.width, event.size.height);
                break;
            case sf::Event::JoystickConnected:
                [[fallthrough]];
            case sf::Event::JoystickDisconnected:
                m_input->initialize_gamepads();
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
                m_input->require_refresh();
                if (event.key.code == sf::Keyboard::Escape)
                    m_window->close();
                break;
            case sf::Event::GainedFocus:
                debug::Log->debug("<Engine> Gaining focus");
                m_input->set_enabled(true);
                break;
            case sf::Event::LostFocus:
                debug::Log->debug("<Engine> Losing focus");
                m_input->set_enabled(false);
                break;
            default:
                break;
            }
        }
    }

    Engine::Engine()
        : m_log(debug::Log)
    {
    }

    Engine::~Engine()
    {
        this->deinit_plugins();
        try
        {
            this->clean();
        }
        catch (BaseException& e)
        {
            debug::Log->error("Failed to properly clean the engine :\n{}", e.what());
        }
        this->purge();
        debug::Log->debug("Engine has been correctly cleaned");
    }

    void Engine::init(const vili::node& arguments)
    {
        m_arguments = arguments;

        this->init_config();
        this->init_logger();
        this->init_script();
        this->init_events();
        this->init_input();
        this->init_window();
        this->init_cursor();
        this->init_framerate();
        // this->init_plugins();
        this->init_resources();
        this->init_scene();
        m_initialized = true;
    }

    void Engine::run() const
    {
        if (!m_initialized)
            throw exceptions::UnitializedEngine(EXC_INFO);

        const std::string boot_script = "*://boot.lua"_fs;
        if (boot_script.empty())
            throw exceptions::BootScriptMissing(system::MountablePath::string_paths(), EXC_INFO);
        const sol::protected_function_result load_result = m_lua->safe_script_file(boot_script);

        if (!load_result.valid())
        {
            const auto err_obj = load_result.get<sol::error>();
            throw exceptions::BootScriptLoadingError(err_obj.what(), EXC_INFO);
        }
        m_window->create();
        const sol::protected_function boot_function
            = (*m_lua)["Game"]["Start"].get<sol::protected_function>();
        try
        {
            script::safe_lua_call(boot_function);
        }
        catch (const BaseException& exc)
        {
            throw exceptions::BootScriptExecutionError(EXC_INFO).nest(exc);
        }

        m_framerate->start();
        const time::TimeUnit start = time::epoch();
        while (m_window->is_open())
        {
            m_framerate->update();

            if (m_framerate->should_update())
            {
                e_game->trigger(events::Game::Update { m_framerate->get_delta_time() });
                this->update();
            }

            if (m_framerate->should_render())
            {
                e_game->trigger(events::Game::Render {});
                this->render();
                m_framerate->reset();
            }
            else
            {
                // m_lua->collect_garbage();
                // m_lua->collect_garbage();
            }
        }
        time::TimeUnit total_time = time::epoch() - start;
        debug::Log->info("Execution completed in {} seconds", total_time);
    }

    audio::AudioManager& Engine::get_audio_manager()
    {
        return m_audio;
    }

    config::ConfigurationManager& Engine::get_configuration_manager()
    {
        return m_config;
    }

    ResourceManager& Engine::get_resource_manager()
    {
        return *m_resources;
    }

    input::InputManager& Engine::get_input_manager() const
    {
        return *m_input;
    }

    time::FramerateManager& Engine::get_framerate_manager() const
    {
        return *m_framerate;
    }

    event::EventManager& Engine::get_event_manager() const
    {
        return *m_events;
    }

    scene::Scene& Engine::get_scene() const
    {
        return *m_scene;
    }

    system::Cursor& Engine::get_cursor() const
    {
        return *m_cursor;
    }

    system::Window& Engine::get_window() const
    {
        return *m_window;
    }

    script::LuaState& Engine::get_lua_state() const
    {
        return *m_lua;
    }

    debug::Logger Engine::get_logger() const
    {
        return m_log.lock();
    }

    const vili::node& Engine::get_arguments() const
    {
        return m_arguments;
    }

    void Engine::update() const
    {
        // Events
        this->handle_window_events();

        m_scene->update();
        m_events->update();
        m_input->update();
        m_cursor->update();
    }

    void Engine::render() const
    {
        if (m_framerate->should_render())
        {
            m_window->clear();
            m_scene->draw(m_window->get_target());
            m_window->display();
        }
    }
}
