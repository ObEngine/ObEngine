#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Utils::String::Bindings
{
    void LoadFunctionSplit(sol::state_view state);
    void LoadFunctionOccurencesInString(sol::state_view state);
    void LoadFunctionIsStringAlpha(sol::state_view state);
    void LoadFunctionIsStringAlphaNumeric(sol::state_view state);
    void LoadFunctionIsStringNumeric(sol::state_view state);
    void LoadFunctionIsStringInt(sol::state_view state);
    void LoadFunctionIsStringFloat(sol::state_view state);
    void LoadFunctionReplace(sol::state_view state);
    void LoadFunctionIsSurroundedBy(sol::state_view state);
    void LoadFunctionGetRandomKey(sol::state_view state);
    void LoadFunctionContains(sol::state_view state);
    void LoadFunctionStartsWith(sol::state_view state);
    void LoadFunctionEndsWith(sol::state_view state);
    void LoadFunctionDistance(sol::state_view state);
    void LoadFunctionSortByDistance(sol::state_view state);
    void LoadFunctionQuote(sol::state_view state);
    void LoadGlobalAlphabet(sol::state_view state);
    void LoadGlobalNumbers(sol::state_view state);
};