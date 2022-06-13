#include <Script/LuaState.hpp>
#include <System/Path.hpp>

namespace obe::script
{
    void LuaState::load_config(const vili::node& config)
    {
        if (config.contains("patchIO") && config.at("patchIO").as_boolean())
        {
            this->safe_script_file("obe://Lib/Internal/Filesystem.lua"_fs);
        }
        std::string garbage_collector_mode = "generational";
        if (config.contains("garbageCollector"))
        {
            garbage_collector_mode = config.at("garbageCollector").as_string();
        }
        this->safe_script("collectgarbage(\"" + garbage_collector_mode + "\");");
    }
}
