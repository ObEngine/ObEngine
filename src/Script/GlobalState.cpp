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
            Bindings::Load(&ScriptEngine, "Core");
            std::cout << "LOADING CORE LIB RESULT ===============>" << std::endl;
            ScriptEngine("print(inspect(Core))");
            Bindings::Load(&ScriptEngine, "SFML");
            Bindings::Load(&ScriptEngine, "Vili");
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
    }
}
