#include <functional>
#include <memory>

#include <sol/sol.hpp>

#include <Debug/Logger.hpp>
#include <Graphics/Color.hpp>
#include <System/Path.hpp>

namespace obe::Bindings
{
    void IndexAllBindings(sol::state_view state);
}

int lua_exception_handler2(lua_State* L,
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

int main(int argc, char** argv)
{
    using namespace obe;

    Debug::InitLogger();
    Debug::Log->set_level(spdlog::level::warn);
    System::MountablePath::LoadMountFile();

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table,
        sol::lib::package, sol::lib::os, sol::lib::coroutine, sol::lib::math,
        sol::lib::count, sol::lib::debug, sol::lib::io, sol::lib::bit32);

    lua.safe_script("LuaCore = {}");
    lua.safe_script_file("Lib/Internal/ScriptInit.lua"_fs);

    Bindings::IndexAllBindings(lua);
    lua.safe_script_file("Lib/Internal/Searcher.lua"_fs);
    lua.safe_script_file("Lib/Internal/Logger.lua"_fs);
    lua.set_exception_handler(&lua_exception_handler2);

    std::string command;
    std::for_each(argv + 1, argv + argc,
        [&](const char* c_str) { command += std::string(c_str) + " "; });

    lua["_term_display"]
        = [](std::vector<std::string> texts, std::vector<obe::Graphics::Color> colors) {
              for (const auto& text : texts)
              {
                  std::cout << text;
              }
              std::cout << std::endl;
          };

    lua.safe_script_file("Lib/Toolkit/Toolkit.lua"_fs);

    lua["evaluate"](command);

    return 0;
}
