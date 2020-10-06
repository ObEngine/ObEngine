#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Bindings::Exceptions::Bindings
{
    void LoadClassBindingTreeNodeNotFound(sol::state_view state);
};