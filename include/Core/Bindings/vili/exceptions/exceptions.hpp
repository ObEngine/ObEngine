#pragma once

namespace sol
{
    class state_view;
};
namespace vili::exceptions::bindings
{
    void load_class_array_index_overflow(sol::state_view state);
    void load_class_base_exception(sol::state_view state);
    void load_class_debug_info(sol::state_view state);
    void load_class_file_not_found(sol::state_view state);
    void load_class_inconsistent_indentation(sol::state_view state);
    void load_class_integer_dump_error(sol::state_view state);
    void load_class_invalid_cast(sol::state_view state);
    void load_class_invalid_data_type(sol::state_view state);
    void load_class_invalid_merge(sol::state_view state);
    void load_class_invalid_node_type(sol::state_view state);
    void load_class_number_dump_error(sol::state_view state);
    void load_class_parsing_error(sol::state_view state);
    void load_class_too_much_indentation(sol::state_view state);
    void load_class_unknown_child_node(sol::state_view state);
};