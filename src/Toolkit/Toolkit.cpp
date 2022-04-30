#include <iostream>
#include <map>
#include <memory>

#include <sol/sol.hpp>
#include <styler/styler.hpp>

#include <Debug/Logger.hpp>
#include <Graphics/Color.hpp>
#include <Script/Scripting.hpp>
#include <System/Path.hpp>

namespace obe::Bindings
{
    void IndexCoreBindings(sol::state_view state);
}

int lua_exception_handler2(lua_State* L, sol::optional<const std::exception&> maybe_exception,
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

styler::Foreground convertColor(obe::Graphics::Color color)
{
    if (color.toName() == "white")
    {
        return styler::Foreground::White;
    }
    else if (color.toName() == "red")
    {
        return styler::Foreground::Red;
    }
    else if (color.toName() == "green")
    {
        return styler::Foreground::Green;
    }
    else if (color.toName() == "blue")
    {
        return styler::Foreground::Blue;
    }
    else if (color.toName() == "yellow")
    {
        return styler::Foreground::Yellow;
    }
    else if (color.toName() == "magenta")
    {
        return styler::Foreground::Magenta;
    }
    else if (color.toName() == "cyan")
    {
        return styler::Foreground::Cyan;
    }
    else if (color.toName() == "black")
    {
        return styler::Foreground::Black;
    }
    else
    {
        return styler::Foreground::White;
    }
}

void run(std::string command)
{
    using namespace obe;

    Debug::InitLogger();
    Debug::Log->set_level(spdlog::level::warn);
    System::MountablePath::LoadMountFile(false, true);

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table, sol::lib::package,
        sol::lib::os, sol::lib::coroutine, sol::lib::math, sol::lib::count, sol::lib::debug,
        sol::lib::io, sol::lib::bit32);
    (*m_lua)["__ENV_ID"] = "[Global Environment]";
    // Table shared across all environments, for easy value sharing
    (*m_lua)["global"] = sol::new_table();

    Bindings::IndexCoreBindings(lua);
    lua.safe_script_file("obe://Lib/Internal/Require.lua"_fs);
    lua.safe_script_file("obe://Lib/Internal/Helpers.lua"_fs);
    lua.safe_script_file("obe://Lib/Internal/Logger.lua"_fs);
    lua.set_exception_handler(&lua_exception_handler2);

    lua["_term_display"]
        = [](std::vector<std::string> texts, std::vector<obe::Graphics::Color> colors) {
              for (size_t i = 0; i < texts.size(); i++)
              {
                  const std::string_view text = texts[i];
                  const Graphics::Color color = colors[i];
                  std::cout << convertColor(color) << text;
              }
              std::cout << std::endl;
          };

    lua.safe_script_file("obe://Lib/Toolkit/Toolkit.lua"_fs);
    lua["TOOLKIT_CONTEXTS"] = std::map<std::string, bool> { { "terminal", true } };

    auto isInteractive = [&lua]() {
        std::map<std::string, bool> contexts
            = lua["TOOLKIT_CONTEXTS"].get<std::map<std::string, bool>>();
        if (contexts.find("interactive") == contexts.end() || !contexts.at("interactive"))
        {
            return false;
        }
        return true;
    };
    Script::safeLuaCall(lua["evaluate"].get<sol::protected_function>(), command);

    if (!isInteractive())
    {
        Script::safeLuaCall(lua["prompt"].get<sol::protected_function>());
    }
}

int main(int argc, char** argv)
{
    using namespace obe;

    std::string command;
    std::for_each(
        argv + 1, argv + argc, [&](const char* c_str) { command += std::string(c_str) + " "; });

#if defined _DEBUG
    run(command);
#else
    try
    {
        run(command);
    }
    catch (const std::exception& e)
    {
        if (Debug::Log)
        {
            Debug::Log->error("The following error occurred while running obey");
            Debug::Log->error(e.what());
        }
        else
        {
            std::cerr << "The following error occurred while running obey" << std::endl;
            std::cerr << e.what() << std::endl;
        }
        return 1;
    }
#endif

    return 0;
}
