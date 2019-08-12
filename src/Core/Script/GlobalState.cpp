#include <Bindings/Bindings.hpp>
#include <Script/GlobalState.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

namespace obe::Script
{
    kaguya::State ScriptEngine;
    void InitScriptEngine()
    {
        System::Path("Lib/Internal/LuaCore.lua").load(System::Loaders::luaLoader, ScriptEngine);
        System::Path("Lib/Internal/Environment.lua").load(System::Loaders::luaLoader, ScriptEngine);
        System::Path("Lib/Internal/ScriptInit.lua").load(System::Loaders::luaLoader, ScriptEngine);
        System::Path("Lib/Internal/Triggers.lua").load(System::Loaders::luaLoader, ScriptEngine);
        Bindings::BindTree(&ScriptEngine);
        ScriptEngine["Hook"] = kaguya::NewTable();
        ScriptEngine.dofile("Lib/Internal/Canvas.lua");
    }

    unsigned int CreateNewEnvironment()
    {
        return ScriptEngine["LuaCore"]["CreateNewEnv"]();
    }

    void executeFile(unsigned int envIndex, const std::string& file)
    {
        ScriptEngine["LuaCore"]["ExecuteFileOnEnv"](System::Path(file).find(), envIndex);
    }

    void executeString(unsigned int envIndex, const std::string& string)
    {
        ScriptEngine["LuaCore"]["ExecuteStringOnEnv"](string, envIndex);
    }
}
