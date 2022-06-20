#pragma once

namespace sol
{
    class state_view;
};
namespace obe::engine::exceptions::bindings
{
    void load_class_boot_script_execution_error(sol::state_view state);
    void load_class_boot_script_loading_error(sol::state_view state);
    void load_class_boot_script_missing(sol::state_view state);
    void load_class_font_not_found(sol::state_view state);
    void load_class_texture_not_found(sol::state_view state);
    void load_class_unitialized_engine(sol::state_view state);
};