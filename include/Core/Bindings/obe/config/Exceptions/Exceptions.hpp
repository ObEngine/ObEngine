#pragma once

namespace sol
{
    class state_view;
};
namespace obe::config::Exceptions::bindings
{
    void load_class_config_error(sol::state_view state);
    void load_class_invalid_version_format(sol::state_view state);
};