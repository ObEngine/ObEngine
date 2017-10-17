#include <Bindings/Bindings.hpp>
#include <Script/GlobalState.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>

namespace obe
{
    namespace Script
    {
        kaguya::State ScriptEngine;

        void InitScriptEngine()
        {
            System::Path("Lib/Internal/Environment.lua").loadResource(&ScriptEngine, System::Loaders::luaLoader);
            System::Path("Lib/Internal/ScriptInit.lua").loadResource(&ScriptEngine, System::Loaders::luaLoader);
            Bindings::Load(&ScriptEngine, "obe");
            Bindings::Load(&ScriptEngine, "SFML");
            Bindings::Load(&ScriptEngine, "Vili");
            Bindings::Load(&ScriptEngine, "Plugins");
            ScriptEngine["Hook"] = kaguya::NewTable();
            ScriptEngine.dofile("Lib/Internal/CanvasConfig.lua");
        }

        unsigned int createNewEnvironment()
        {
            return ScriptEngine["CreateNewEnv"]();
        }

        void executeFile(unsigned envIndex, const std::string& file)
        {
            ScriptEngine["ExecuteFileOnEnv"](System::Path(file).find(), envIndex);
        }

        void executeString(unsigned envIndex, const std::string& string)
        {
            ScriptEngine["ExecuteStringOnEnv"](string, envIndex);
        }
    }
}
