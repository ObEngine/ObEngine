#pragma once

namespace sol
{
    class state_view;
};
namespace vili::parser::rules::bindings
{
    void load_class_affectation(sol::state_view state);
    void load_class_affectation_separator(sol::state_view state);
    void load_class_array(sol::state_view state);
    void load_class_array_elements(sol::state_view state);
    void load_class_array_separator(sol::state_view state);
    void load_class_block(sol::state_view state);
    void load_class_boolean(sol::state_view state);
    void load_class_brace_based_object(sol::state_view state);
    void load_class_char_(sol::state_view state);
    void load_class_close_array(sol::state_view state);
    void load_class_close_object(sol::state_view state);
    void load_class_comment(sol::state_view state);
    void load_class_data(sol::state_view state);
    void load_class_digits(sol::state_view state);
    void load_class_element(sol::state_view state);
    void load_class_empty_line(sol::state_view state);
    void load_class_endline(sol::state_view state);
    void load_class_escaped(sol::state_view state);
    void load_class_escaped_char(sol::state_view state);
    void load_class_false_(sol::state_view state);
    void load_class_floating_point(sol::state_view state);
    void load_class_full_node(sol::state_view state);
    void load_class_grammar(sol::state_view state);
    void load_class_identifier(sol::state_view state);
    void load_class_indent(sol::state_view state);
    void load_class_indent_based_object(sol::state_view state);
    void load_class_inline_comment(sol::state_view state);
    void load_class_inline_element(sol::state_view state);
    void load_class_inline_node(sol::state_view state);
    void load_class_integer(sol::state_view state);
    void load_class_multiline_comment(sol::state_view state);
    void load_class_multiline_comment_block(sol::state_view state);
    void load_class_node(sol::state_view state);
    void load_class_number(sol::state_view state);
    void load_class_object(sol::state_view state);
    void load_class_object_elements(sol::state_view state);
    void load_class_object_separator(sol::state_view state);
    void load_class_open_array(sol::state_view state);
    void load_class_open_object(sol::state_view state);
    void load_class_sign(sol::state_view state);
    void load_class_space_or_comment(sol::state_view state);
    void load_class_string(sol::state_view state);
    void load_class_string_content(sol::state_view state);
    void load_class_string_delimiter(sol::state_view state);
    void load_class_true_(sol::state_view state);
    void load_class_unescaped(sol::state_view state);
    void load_class_unicode(sol::state_view state);
    void load_class_vili_grammar(sol::state_view state);
    void load_class_xdigit(sol::state_view state);
}; // namespace vili::parser::rules::bindings