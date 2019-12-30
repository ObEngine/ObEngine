#include <Bindings/DebugBindings.hpp>
#include <Debug/Logger.hpp>

#include <Script/GlobalState.hpp>
#include <System/Loaders.hpp>
#include <System/Path.hpp>
#include <kaguya/kaguya.hpp>

namespace obe::Bindings::DebugBindings
{
    void LoadLog(kaguya::State* lua)
    {
        (*lua)["obe"]["Debug"] = kaguya::NewTable();
        (*lua)["obe"]["Debug"]["setLevel"] = kaguya::function(Debug::SetLoggerLevel);
        (*lua)["obe"]["Debug"]["__critical_internal"]
            = kaguya::function([](const std::string& str) { Debug::Log->critical(str); });
        (*lua)["obe"]["Debug"]["__error_internal"]
            = kaguya::function([](const std::string& str) { Debug::Log->error(str); });
        (*lua)["obe"]["Debug"]["__warn_internal"]
            = kaguya::function([](const std::string& str) { Debug::Log->warn(str); });
        (*lua)["obe"]["Debug"]["__info_internal"]
            = kaguya::function([](const std::string& str) { Debug::Log->info(str); });
        (*lua)["obe"]["Debug"]["__debug_internal"]
            = kaguya::function([](const std::string& str) { Debug::Log->debug(str); });
        (*lua)["obe"]["Debug"]["__trace_internal"]
            = kaguya::function([](const std::string& str) { Debug::Log->trace(str); });
        System::Path("Lib/Internal/Debug.lua")
            .load(System::Loaders::luaLoader, Script::ScriptEngine);
    }
} // namespace obe::Bindings::DebugBindings
