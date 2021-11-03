#include <Script/LuaState.hpp>
#include <System/Path.hpp>

namespace obe::Script
{
    void LuaState::loadConfig(const vili::node& config)
    {
        if (config.contains("patchIO") && config.at("patchIO").as_boolean())
        {
            this->safe_script_file("obe://Lib/Internal/Filesystem.lua"_fs);
        }
        std::string garbageCollectorMode = "generational";
        if (config.contains("garbageCollector"))
        {
            garbageCollectorMode = config.at("garbageCollector").as_string();
        }
        this->safe_script("collectgarbage(\"" + garbageCollectorMode + "\");");
    }
}
