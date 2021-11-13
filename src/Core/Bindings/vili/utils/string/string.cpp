#include <Bindings/vili/utils/string/string.hpp>

#include <vili/utils.hpp>

#include <Bindings/Config.hpp>

namespace vili::utils::string::Bindings
{
    void LoadFunctionReplace(sol::state_view state)
    {
        sol::table stringNamespace = state["vili"]["utils"]["string"].get<sol::table>();
        stringNamespace.set_function("replace", &vili::utils::string::replace);
    }
    void LoadFunctionIsInt(sol::state_view state)
    {
        sol::table stringNamespace = state["vili"]["utils"]["string"].get<sol::table>();
        stringNamespace.set_function("is_int", &vili::utils::string::is_int);
    }
    void LoadFunctionIsFloat(sol::state_view state)
    {
        sol::table stringNamespace = state["vili"]["utils"]["string"].get<sol::table>();
        stringNamespace.set_function("is_float", &vili::utils::string::is_float);
    }
    void LoadFunctionTruncateFloat(sol::state_view state)
    {
        sol::table stringNamespace = state["vili"]["utils"]["string"].get<sol::table>();
        stringNamespace.set_function("truncate_float", &vili::utils::string::truncate_float);
    }
    void LoadFunctionQuote(sol::state_view state)
    {
        sol::table stringNamespace = state["vili"]["utils"]["string"].get<sol::table>();
        stringNamespace.set_function("quote", &vili::utils::string::quote);
    }
    void LoadFunctionToDouble(sol::state_view state)
    {
        sol::table stringNamespace = state["vili"]["utils"]["string"].get<sol::table>();
        stringNamespace.set_function("to_double", &vili::utils::string::to_double);
    }
    void LoadFunctionToLong(sol::state_view state)
    {
        sol::table stringNamespace = state["vili"]["utils"]["string"].get<sol::table>();
        stringNamespace.set_function("to_long", &vili::utils::string::to_long);
    }
    void LoadFunctionIndent(sol::state_view state)
    {
        sol::table stringNamespace = state["vili"]["utils"]["string"].get<sol::table>();
        stringNamespace.set_function("indent",
            sol::overload([](const std::string& input) -> std::string
                { return vili::utils::string::indent(input); },
                [](const std::string& input, unsigned int indent_level) -> std::string
                { return vili::utils::string::indent(input, indent_level); },
                [](const std::string& input, unsigned int indent_level,
                    bool pad_left) -> std::string
                { return vili::utils::string::indent(input, indent_level, pad_left); }));
    }
    void LoadFunctionDistance(sol::state_view state)
    {
        sol::table stringNamespace = state["vili"]["utils"]["string"].get<sol::table>();
        stringNamespace.set_function("distance", &vili::utils::string::distance);
    }
    void LoadFunctionSortByDistance(sol::state_view state)
    {
        sol::table stringNamespace = state["vili"]["utils"]["string"].get<sol::table>();
        stringNamespace.set_function("sort_by_distance", &vili::utils::string::sort_by_distance);
    }
};