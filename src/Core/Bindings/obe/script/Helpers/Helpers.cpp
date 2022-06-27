#include <Bindings/obe/script/Helpers/Helpers.hpp>

#include <Script/LuaHelpers.hpp>

#include <Bindings/Config.hpp>

namespace obe::script::Helpers::bindings
{
    void load_function_make_all_helpers(sol::state_view state)
    {
        sol::table Helpers_namespace = state["obe"]["script"]["Helpers"].get<sol::table>();
        Helpers_namespace.set_function("make_all_helpers", &obe::script::Helpers::make_all_helpers);
    }
    void load_function_fetch_from_one_of(sol::state_view state)
    {
        sol::table Helpers_namespace = state["obe"]["script"]["Helpers"].get<sol::table>();
        Helpers_namespace.set_function(
            "fetch_from_one_of", &obe::script::Helpers::fetch_from_one_of);
    }
    void load_function_rawget_from(sol::state_view state)
    {
        sol::table Helpers_namespace = state["obe"]["script"]["Helpers"].get<sol::table>();
        Helpers_namespace.set_function("rawget_from", &obe::script::Helpers::rawget_from);
    }
    void load_function_len_from(sol::state_view state)
    {
        sol::table Helpers_namespace = state["obe"]["script"]["Helpers"].get<sol::table>();
        Helpers_namespace.set_function("len_from", &obe::script::Helpers::len_from);
    }
    void load_function_pairs_from(sol::state_view state)
    {
        sol::table Helpers_namespace = state["obe"]["script"]["Helpers"].get<sol::table>();
        Helpers_namespace.set_function("pairs_from", &obe::script::Helpers::pairs_from);
    }
};