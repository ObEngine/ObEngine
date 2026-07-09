#include <Bindings/obe/utils/string/String.hpp>

#include <Utils/StringUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::utils::string::bindings
{
    void load_function_split(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("split",
            sol::overload(
                [](const std::string& str) -> std::vector<std::string> {
                    return obe::utils::string::split(str);
                },
                [](const std::string& str,
                    const std::string& delimiters) -> std::vector<std::string> {
                    return obe::utils::string::split(str, delimiters);
                }));
    }
    void load_function_occurences_in_string(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function(
            "occurences_in_string", &obe::utils::string::occurences_in_string);
    }
    void load_function_is_string_alpha(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("is_string_alpha", &obe::utils::string::is_string_alpha);
    }
    void load_function_is_string_alpha_numeric(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function(
            "is_string_alpha_numeric", &obe::utils::string::is_string_alpha_numeric);
    }
    void load_function_is_string_numeric(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("is_string_numeric", &obe::utils::string::is_string_numeric);
    }
    void load_function_is_string_int(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("is_string_int", &obe::utils::string::is_string_int);
    }
    void load_function_is_string_float(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("is_string_float", &obe::utils::string::is_string_float);
    }
    void load_function_replace(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("replace", &obe::utils::string::replace);
    }
    void load_function_is_surrounded_by(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("is_surrounded_by", &obe::utils::string::is_surrounded_by);
    }
    void load_function_get_random_key(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("get_random_key", &obe::utils::string::get_random_key);
    }
    void load_function_contains(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("contains", &obe::utils::string::contains);
    }
    void load_function_starts_with(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("starts_with", &obe::utils::string::starts_with);
    }
    void load_function_ends_with(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("ends_with", &obe::utils::string::ends_with);
    }
    void load_function_distance(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("distance", &obe::utils::string::distance);
    }
    void load_function_sort_by_distance(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("sort_by_distance",
            sol::overload(
                [](const std::string& source,
                    const std::vector<std::string>& words) -> std::vector<std::string> {
                    return obe::utils::string::sort_by_distance(source, words);
                },
                [](const std::string& source, const std::vector<std::string>& words,
                    std::size_t limit) -> std::vector<std::string> {
                    return obe::utils::string::sort_by_distance(source, words, limit);
                }));
    }
    void load_function_quote(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("quote", &obe::utils::string::quote);
    }
    void load_function_titleize(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace.set_function("titleize", &obe::utils::string::titleize);
    }
    void load_global_alphabet(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace["Alphabet"] = obe::utils::string::Alphabet;
    }
    void load_global_numbers(sol::state_view state)
    {
        sol::table string_namespace = state["obe"]["utils"]["string"].get<sol::table>();
        string_namespace["Numbers"] = obe::utils::string::Numbers;
    }
};