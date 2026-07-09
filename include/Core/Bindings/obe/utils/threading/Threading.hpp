#pragma once

namespace sol
{
    class state_view;
};
namespace obe::utils::threading::bindings
{
    void load_class_thread(sol::state_view state);
};