#include <Bindings/vili/parser/rules/Rules.hpp>

#include <vili/parser/grammar.hpp>

#include <Bindings/Config.hpp>

namespace vili::parser::rules::bindings
{
    void load_class_affectation(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::affectation> bind_affectation
            = rules_namespace.new_usertype<vili::parser::rules::affectation>(
                "affectation", sol::call_constructor, sol::default_constructor);
    }
    void load_class_affectation_separator(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::affectation_separator> bind_affectation_separator
            = rules_namespace.new_usertype<vili::parser::rules::affectation_separator>(
                "affectation_separator", sol::call_constructor, sol::default_constructor);
    }
    void load_class_array(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::array> bind_array
            = rules_namespace.new_usertype<vili::parser::rules::array>(
                "array", sol::call_constructor, sol::default_constructor);
    }
    void load_class_array_elements(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::array_elements> bind_array_elements
            = rules_namespace.new_usertype<vili::parser::rules::array_elements>(
                "array_elements", sol::call_constructor, sol::default_constructor);
    }
    void load_class_array_separator(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::array_separator> bind_array_separator
            = rules_namespace.new_usertype<vili::parser::rules::array_separator>(
                "array_separator", sol::call_constructor, sol::default_constructor);
    }
    void load_class_block(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::block> bind_block
            = rules_namespace.new_usertype<vili::parser::rules::block>(
                "block", sol::call_constructor, sol::default_constructor);
    }
    void load_class_boolean(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::boolean> bind_boolean
            = rules_namespace.new_usertype<vili::parser::rules::boolean>(
                "boolean", sol::call_constructor, sol::default_constructor);
    }
    void load_class_brace_based_object(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::brace_based_object> bind_brace_based_object
            = rules_namespace.new_usertype<vili::parser::rules::brace_based_object>(
                "brace_based_object", sol::call_constructor, sol::default_constructor);
    }
    void load_class_char_(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::char_> bind_char_
            = rules_namespace.new_usertype<vili::parser::rules::char_>(
                "char_", sol::call_constructor, sol::default_constructor);
    }
    void load_class_close_array(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::close_array> bind_close_array
            = rules_namespace.new_usertype<vili::parser::rules::close_array>(
                "close_array", sol::call_constructor, sol::default_constructor);
    }
    void load_class_close_object(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::close_object> bind_close_object
            = rules_namespace.new_usertype<vili::parser::rules::close_object>(
                "close_object", sol::call_constructor, sol::default_constructor);
    }
    void load_class_comment(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::comment> bind_comment
            = rules_namespace.new_usertype<vili::parser::rules::comment>(
                "comment", sol::call_constructor, sol::default_constructor);
    }
    void load_class_data(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::data> bind_data
            = rules_namespace.new_usertype<vili::parser::rules::data>(
                "data", sol::call_constructor, sol::default_constructor);
    }
    void load_class_digits(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::digits> bind_digits
            = rules_namespace.new_usertype<vili::parser::rules::digits>(
                "digits", sol::call_constructor, sol::default_constructor);
    }
    void load_class_element(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::element> bind_element
            = rules_namespace.new_usertype<vili::parser::rules::element>(
                "element", sol::call_constructor, sol::default_constructor);
    }
    void load_class_empty_line(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::empty_line> bind_empty_line
            = rules_namespace.new_usertype<vili::parser::rules::empty_line>(
                "empty_line", sol::call_constructor, sol::default_constructor);
    }
    void load_class_endline(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::endline> bind_endline
            = rules_namespace.new_usertype<vili::parser::rules::endline>(
                "endline", sol::call_constructor, sol::default_constructor);
    }
    void load_class_escaped(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::escaped> bind_escaped
            = rules_namespace.new_usertype<vili::parser::rules::escaped>(
                "escaped", sol::call_constructor, sol::default_constructor);
    }
    void load_class_escaped_char(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::escaped_char> bind_escaped_char
            = rules_namespace.new_usertype<vili::parser::rules::escaped_char>(
                "escaped_char", sol::call_constructor, sol::default_constructor);
    }
    void load_class_false_(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::false_> bind_false_
            = rules_namespace.new_usertype<vili::parser::rules::false_>(
                "false_", sol::call_constructor, sol::default_constructor);
    }
    void load_class_floating_point(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::floating_point> bind_floating_point
            = rules_namespace.new_usertype<vili::parser::rules::floating_point>(
                "floating_point", sol::call_constructor, sol::default_constructor);
    }
    void load_class_full_node(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::full_node> bind_full_node
            = rules_namespace.new_usertype<vili::parser::rules::full_node>(
                "full_node", sol::call_constructor, sol::default_constructor);
    }
    void load_class_grammar(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::grammar> bind_grammar
            = rules_namespace.new_usertype<vili::parser::rules::grammar>(
                "grammar", sol::call_constructor, sol::default_constructor);
    }
    void load_class_identifier(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::identifier> bind_identifier
            = rules_namespace.new_usertype<vili::parser::rules::identifier>(
                "identifier", sol::call_constructor, sol::default_constructor);
    }
    void load_class_indent(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::indent> bind_indent
            = rules_namespace.new_usertype<vili::parser::rules::indent>(
                "indent", sol::call_constructor, sol::default_constructor);
    }
    void load_class_indent_based_object(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::indent_based_object> bind_indent_based_object
            = rules_namespace.new_usertype<vili::parser::rules::indent_based_object>(
                "indent_based_object", sol::call_constructor, sol::default_constructor);
    }
    void load_class_inline_comment(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::inline_comment> bind_inline_comment
            = rules_namespace.new_usertype<vili::parser::rules::inline_comment>(
                "inline_comment", sol::call_constructor, sol::default_constructor);
    }
    void load_class_inline_element(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::inline_element> bind_inline_element
            = rules_namespace.new_usertype<vili::parser::rules::inline_element>(
                "inline_element", sol::call_constructor, sol::default_constructor);
    }
    void load_class_inline_node(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::inline_node> bind_inline_node
            = rules_namespace.new_usertype<vili::parser::rules::inline_node>(
                "inline_node", sol::call_constructor, sol::default_constructor);
    }
    void load_class_integer(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::integer> bind_integer
            = rules_namespace.new_usertype<vili::parser::rules::integer>(
                "integer", sol::call_constructor, sol::default_constructor);
    }
    void load_class_multiline_comment(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::multiline_comment> bind_multiline_comment
            = rules_namespace.new_usertype<vili::parser::rules::multiline_comment>(
                "multiline_comment", sol::call_constructor, sol::default_constructor);
    }
    void load_class_multiline_comment_block(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::multiline_comment_block> bind_multiline_comment_block
            = rules_namespace.new_usertype<vili::parser::rules::multiline_comment_block>(
                "multiline_comment_block", sol::call_constructor, sol::default_constructor);
    }
    void load_class_node(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::node> bind_node
            = rules_namespace.new_usertype<vili::parser::rules::node>(
                "node", sol::call_constructor, sol::default_constructor);
    }
    void load_class_number(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::number> bind_number
            = rules_namespace.new_usertype<vili::parser::rules::number>(
                "number", sol::call_constructor, sol::default_constructor);
    }
    void load_class_object(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::object> bind_object
            = rules_namespace.new_usertype<vili::parser::rules::object>(
                "object", sol::call_constructor, sol::default_constructor);
    }
    void load_class_object_elements(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::object_elements> bind_object_elements
            = rules_namespace.new_usertype<vili::parser::rules::object_elements>(
                "object_elements", sol::call_constructor, sol::default_constructor);
    }
    void load_class_object_separator(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::object_separator> bind_object_separator
            = rules_namespace.new_usertype<vili::parser::rules::object_separator>(
                "object_separator", sol::call_constructor, sol::default_constructor);
    }
    void load_class_open_array(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::open_array> bind_open_array
            = rules_namespace.new_usertype<vili::parser::rules::open_array>(
                "open_array", sol::call_constructor, sol::default_constructor);
    }
    void load_class_open_object(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::open_object> bind_open_object
            = rules_namespace.new_usertype<vili::parser::rules::open_object>(
                "open_object", sol::call_constructor, sol::default_constructor);
    }
    void load_class_sign(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::sign> bind_sign
            = rules_namespace.new_usertype<vili::parser::rules::sign>(
                "sign", sol::call_constructor, sol::default_constructor);
    }
    void load_class_space_or_comment(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::space_or_comment> bind_space_or_comment
            = rules_namespace.new_usertype<vili::parser::rules::space_or_comment>(
                "space_or_comment", sol::call_constructor, sol::default_constructor);
    }
    void load_class_string(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::string> bind_string
            = rules_namespace.new_usertype<vili::parser::rules::string>(
                "string", sol::call_constructor, sol::default_constructor);
    }
    void load_class_string_content(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::string_content> bind_string_content
            = rules_namespace.new_usertype<vili::parser::rules::string_content>(
                "string_content", sol::call_constructor, sol::default_constructor);
    }
    void load_class_string_delimiter(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::string_delimiter> bind_string_delimiter
            = rules_namespace.new_usertype<vili::parser::rules::string_delimiter>(
                "string_delimiter", sol::call_constructor, sol::default_constructor);
    }
    void load_class_true_(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::true_> bind_true_
            = rules_namespace.new_usertype<vili::parser::rules::true_>(
                "true_", sol::call_constructor, sol::default_constructor);
    }
    void load_class_unescaped(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::unescaped> bind_unescaped
            = rules_namespace.new_usertype<vili::parser::rules::unescaped>(
                "unescaped", sol::call_constructor, sol::default_constructor);
    }
    void load_class_unicode(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::unicode> bind_unicode
            = rules_namespace.new_usertype<vili::parser::rules::unicode>(
                "unicode", sol::call_constructor, sol::default_constructor);
    }
    void load_class_vili_grammar(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::vili_grammar> bind_vili_grammar
            = rules_namespace.new_usertype<vili::parser::rules::vili_grammar>(
                "vili_grammar", sol::call_constructor, sol::default_constructor);
    }
    void load_class_xdigit(sol::state_view state)
    {
        sol::table rules_namespace = state["vili"]["parser"]["rules"].get<sol::table>();
        sol::usertype<vili::parser::rules::xdigit> bind_xdigit
            = rules_namespace.new_usertype<vili::parser::rules::xdigit>(
                "xdigit", sol::call_constructor, sol::default_constructor);
    }
};