#include <Bindings/obe/Utils/String/String.hpp>

#include <Utils/StringUtils.hpp>

#include <Bindings/Config.hpp>

namespace obe::Utils::String::Bindings
{
    void LoadFunctionSplit(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("split", obe::Utils::String::split);
    }
    void LoadFunctionOccurencesInString(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function(
            "occurencesInString", obe::Utils::String::occurencesInString);
    }
    void LoadFunctionIsStringAlpha(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("isStringAlpha", obe::Utils::String::isStringAlpha);
    }
    void LoadFunctionIsStringAlphaNumeric(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function(
            "isStringAlphaNumeric", obe::Utils::String::isStringAlphaNumeric);
    }
    void LoadFunctionIsStringNumeric(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function(
            "isStringNumeric", obe::Utils::String::isStringNumeric);
    }
    void LoadFunctionIsStringInt(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("isStringInt", obe::Utils::String::isStringInt);
    }
    void LoadFunctionIsStringFloat(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("isStringFloat", obe::Utils::String::isStringFloat);
    }
    void LoadFunctionReplace(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("replace", obe::Utils::String::replace);
    }
    void LoadFunctionIsSurroundedBy(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function(
            "isSurroundedBy", obe::Utils::String::isSurroundedBy);
    }
    void LoadFunctionGetRandomKey(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("getRandomKey", obe::Utils::String::getRandomKey);
    }
    void LoadFunctionContains(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("contains", obe::Utils::String::contains);
    }
    void LoadFunctionStartsWith(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("startsWith", obe::Utils::String::startsWith);
    }
    void LoadFunctionEndsWith(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("endsWith", obe::Utils::String::endsWith);
    }
    void LoadFunctionDistance(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("distance", obe::Utils::String::distance);
    }
    void LoadFunctionSortByDistance(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function(
            "sortByDistance", obe::Utils::String::sortByDistance);
    }
    void LoadFunctionQuote(sol::state_view state)
    {
        sol::table StringNamespace = state["obe"]["Utils"]["String"].get<sol::table>();
        StringNamespace.set_function("quote", obe::Utils::String::quote);
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