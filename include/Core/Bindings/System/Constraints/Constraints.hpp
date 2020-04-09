#pragma once

namespace sol
{
    class state_view;
};
namespace obe::System::Constraints::Bindings
{
    void LoadGlobalDefault(sol::state_view state);
};