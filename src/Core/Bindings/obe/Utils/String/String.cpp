#include <Bindings/obe/Utils/String/String.hpp>

#include <Utils/StringUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::Utils::String::Bindings
{
    void LoadFunctionSplit(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("split",
            sol::overload(
                [](const std::string& str) -> std::vector<std::string> {
                    return obe::Utils::String::split(str);
                },
                [](const std::string& str,
                    const std::string& delimiters) -> std::vector<std::string> {
                    return obe::Utils::String::split(str, delimiters);
                }));
    }
    void LoadFunctionOccurencesInString(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("occurences_in_string", &obe::Utils::String::occurences_in_string);
    }
    void LoadFunctionIsStringAlpha(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("is_string_alpha", &obe::Utils::String::is_string_alpha);
    }
    void LoadFunctionIsStringAlphaNumeric(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function(
            "is_string_alpha_numeric", &obe::Utils::String::is_string_alpha_numeric);
    }
    void LoadFunctionIsStringNumeric(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("is_string_numeric", &obe::Utils::String::is_string_numeric);
    }
    void LoadFunctionIsStringInt(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("is_string_int", &obe::Utils::String::is_string_int);
    }
    void LoadFunctionIsStringFloat(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("is_string_float", &obe::Utils::String::is_string_float);
    }
    void LoadFunctionReplace(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("replace", &obe::Utils::String::replace);
    }
    void LoadFunctionIsSurroundedBy(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("is_surrounded_by", &obe::Utils::String::is_surrounded_by);
    }
    void LoadFunctionGetRandomKey(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("get_random_key", &obe::Utils::String::get_random_key);
    }
    void LoadFunctionContains(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("contains", &obe::Utils::String::contains);
    }
    void LoadFunctionStartsWith(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("starts_with", &obe::Utils::String::starts_with);
    }
    void LoadFunctionEndsWith(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("ends_with", &obe::Utils::String::ends_with);
    }
    void LoadFunctionDistance(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("distance", &obe::Utils::String::distance);
    }
    void LoadFunctionSortByDistance(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("sort_by_distance",
            sol::overload(
                [](const std::string& source,
                    const std::vector<std::string>& words) -> std::vector<std::string> {
                    return obe::Utils::String::sort_by_distance(source, words);
                },
                [](const std::string& source, const std::vector<std::string>& words,
                    std::size_t limit) -> std::vector<std::string> {
                    return obe::Utils::String::sort_by_distance(source, words, limit);
                }));
    }
    void LoadFunctionQuote(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("quote", &obe::Utils::String::quote);
    }
    void LoadGlobalAlphabet(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace["Alphabet"] = obe::Utils::String::Alphabet;
    }
    void LoadGlobalNumbers(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace["Numbers"] = obe::Utils::String::Numbers;
    }
};