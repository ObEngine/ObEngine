#pragma once

namespace sol
{
    class state_view;
};
namespace vili::utils::string::Bindings
{
    void LoadFunctionReplace(sol::state_view state);
    void LoadFunctionIsInt(sol::state_view state);
    void LoadFunctionIsFloat(sol::state_view state);
    void LoadFunctionTruncateFloat(sol::state_view state);
    void LoadFunctionQuote(sol::state_view state);
    void LoadFunctionToDouble(sol::state_view state);
    void LoadFunctionToLong(sol::state_view state);
};