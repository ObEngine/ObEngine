#pragma once

namespace sol
{
    class state_view;
};
namespace obe::System::Exceptions::Bindings
{
    void LoadClassResourceNotFound(sol::state_view state);
};