#pragma once

namespace sol
{
    class state_view;
};
namespace obe::events::Input::bindings
{
    void load_class_text_entered(sol::state_view state);
};