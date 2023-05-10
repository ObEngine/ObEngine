#include <Bindings/vili/utils/string/String.hpp>

#include <vili/utils.hpp>

#include <Bindings/Config.hpp>

namespace vili::utils::string::bindings
{
    void load_function_replace(sol::state_view state)
    {
        sol::table string_namespace = state["vili"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("replace", &vili::utils::string::replace);
    }
    void load_function_is_int(sol::state_view state)
    {
        sol::table string_namespace = state["vili"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("is_int", &vili::utils::string::is_int);
    }
    void load_function_is_float(sol::state_view state)
    {
        sol::table string_namespace = state["vili"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("is_float", &vili::utils::string::is_float);
    }
    void load_function_truncate_float(sol::state_view state)
    {
        sol::table string_namespace = state["vili"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("truncate_float", &vili::utils::string::truncate_float);
    }
    void load_function_quote(sol::state_view state)
    {
        sol::table string_namespace = state["vili"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("quote", &vili::utils::string::quote);
    }
    void load_function_to_double(sol::state_view state)
    {
        sol::table string_namespace = state["vili"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("to_double", &vili::utils::string::to_double);
    }
    void load_function_to_long(sol::state_view state)
    {
        sol::table string_namespace = state["vili"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("to_long", &vili::utils::string::to_long);
    }
    void load_function_indent(sol::state_view state)
    {
        sol::table string_namespace = state["vili"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("indent",
            sol::overload(
                [](const std::string& input) -> std::string
                {
                    return vili::utils::string::indent(input);
                },
                [](const std::string& input, unsigned int indent_level) -> std::string
                {
                    return vili::utils::string::indent(input, indent_level);
                },
                [](const std::string& input, unsigned int indent_level,
                    bool pad_left) -> std::string
                {
                    return vili::utils::string::indent(input, indent_level, pad_left);
                }));
    }
    void load_function_distance(sol::state_view state)
    {
        sol::table string_namespace = state["vili"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("distance", &vili::utils::string::distance);
    }
    void load_function_sort_by_distance(sol::state_view state)
    {
        sol::table string_namespace = state["vili"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("sort_by_distance", &vili::utils::string::sort_by_distance);
    }
};