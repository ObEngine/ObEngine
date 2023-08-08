#include <Core/Scripting.hpp>

namespace obe::script
{
    std::unique_ptr<sol::state> make_lua_state()
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

        m_lua->safe_script_file("intlibs://Helpers.lua"_fs);
        m_lua->safe_script_file("intlibs://Events.lua"_fs);
        m_lua->safe_script_file("intlibs://GameInit.lua"_fs);
        m_lua->safe_script_file("intlibs://Logger.lua"_fs);
        m_lua->set_exception_handler(&lua_exception_handler);
        m_lua->safe_script("collectgarbage(\"generational\");");

        (*m_lua)["Engine"] = this;
    }
    std::string sol_call_status_to_string(sol::call_status status)
    {
        switch (status)
        {
        case sol::call_status::ok:
            return "ok";
        case sol::call_status::yielded:
            return "yielded";
        case sol::call_status::runtime:
            return "runtime_error";
        case sol::call_status::memory:
            return "memory_error";
        case sol::call_status::handler:
            return "handler_error";
        case sol::call_status::gc:
            return "gc_error";
        case sol::call_status::syntax:
            return "syntax_error";
        case sol::call_status::file:
            return "file_error";
        }
        return "?";
    }
}