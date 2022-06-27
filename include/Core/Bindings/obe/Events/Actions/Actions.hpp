#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::Actions::bindings
{
    void load_class_action(sol::state_view state);
};