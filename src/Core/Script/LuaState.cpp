#include <Script/LuaState.hpp>
#include <Script/Scripting.hpp>
#include <Script/ViliLuaBridge.hpp>
#include <System/Path.hpp>

namespace obe::script
{
    void LuaState::load_config(const vili::node& config)
    {
        if (config.contains("features"))
        {
            auto features = script::vili_lua_bridge::vili_to_lua(config.at("features"));
            auto features_configurator = this->safe_script_file("obe://Lib/Helpers/Helpers.lua");
            script::safe_lua_call(features_configurator.get<sol::table>()["load_features"], features);
        }
        std::string garbage_collector_mode = "generational";
        if (config.contains("gc"))
        {
            garbage_collector_mode = config.at("gc").as_string();
        }
        this->safe_script("collectgarbage(\"" + garbage_collector_mode + "\");");
    }
}
