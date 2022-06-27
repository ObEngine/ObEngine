#pragma once

namespace sol
{
    class state_view;
};
namespace obe::config::bindings
{
    void load_class_configuration_manager(sol::state_view state);
    void load_class_version(sol::state_view state);
};