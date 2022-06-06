#pragma once

#include <tao/pegtl.hpp>

namespace vili::parser::rules
{
    namespace peg = tao::pegtl;
    // clang-format off
    struct identifier : peg::identifier {};
    struct indent : peg::seq<peg::bol, peg::star<peg::blank>> {};
    struct affectation_separator : peg::one<':'> {};
    struct affectation : peg::seq<identifier, peg::pad<peg::must<affectation_separator>, peg::blank>> {};

    // String
    struct string_delimiter : peg::one<'"'> {};
    struct xdigit : peg::xdigit {};
    struct unicode : peg::list<peg::seq<peg::one<'u'>, peg::rep<4, peg::must< xdigit>>>, peg::one<'\\'>> {};
    struct escaped_char : peg::one< '"', '\\', '/', 'b', 'f', 'n', 'r', 't'> {};
    struct escaped : peg::sor<escaped_char, unicode> {};
    struct unescaped : peg::utf8::range< 0x20, 0x10FFFF> {};
    struct char_ : peg::if_then_else<peg::one<'\\'>, peg::must<escaped>, unescaped> {};

    struct string_content : peg::until<peg::at<string_delimiter>, peg::must<char_>> {};
    struct string : peg::seq<string_delimiter, peg::must<string_content>, peg::any> {};

    // struct string_content : peg::star<char_> {};
    // struct string : peg::seq<string_delimiter, string_content, peg::must<string_delimiter>> {};

    // Booleans
    struct true_ : peg::string<'t', 'r', 'u', 'e'> {};
    struct false_ : peg::string<'f', 'a', 'l', 's', 'e'> {};
    struct boolean : peg::sor<true_, false_> {};

    // Numbers
    struct digits : peg::plus<peg::digit> {};
    struct sign : peg::one<'-'> {};
    struct integer : peg::seq<peg::opt<sign>, digits> {};
    struct floating_point : peg::one<'.'> {};
    struct number : peg::seq<peg::opt<sign>, peg::star<peg::digit>, peg::one<'.'>, digits> {};

    // Data
    struct data : peg::sor<boolean, number, integer, string> {};
    struct brace_based_object;
    struct array;
    struct object;
    struct inline_element : peg::sor<boolean, number, integer, string, array, brace_based_object> {};
    struct inline_node : peg::seq<affectation, inline_element> {};
    struct element : peg::sor<data, array, object> {};

    // Comments
    struct inline_comment : peg::seq<peg::star<peg::blank>, peg::one<'#'>, peg::until<peg::eolf>> {};
    struct multiline_comment : peg::seq<peg::string<'/', '*'>, peg::until<peg::string<'*', '/'>, peg::sor<multiline_comment, peg::any>>> {};
    struct comment : peg::sor<inline_comment, multiline_comment> {};
    struct space_or_comment : peg::sor<comment, peg::space> {};
    struct endline : peg::sor<inline_comment, peg::eol> {};
    struct multiline_comment_block : peg::seq<peg::plus<peg::pad<multiline_comment, peg::blank>>, peg::sor<endline, peg::eolf>> {};

    // Arrays
    struct array_separator : peg::one<','> {};
    struct array_elements : peg::list_must<inline_element, array_separator, space_or_comment> {};
    struct open_array : peg::one<'['> {};
    struct close_array : peg::one<']'> {};
    struct array : peg::seq<open_array, peg::pad_opt<array_elements, space_or_comment>, peg::must<close_array>> {};

    // Objects
    struct node;
    struct indent_based_object : peg::sor<endline, peg::seq<multiline_comment, peg::eol>> {};
    struct open_object : peg::one<'{'> {};
    struct close_object : peg::one<'}'> {};
    struct object_separator : peg::one<','> {};
    struct object_elements : peg::list_must<inline_node, object_separator, space_or_comment> {};
    struct brace_based_object : peg::seq<open_object, peg::pad_opt<object_elements, space_or_comment>, peg::must<close_object>> {};
    struct object : peg::sor<brace_based_object, indent_based_object> {};

    // Nodes
    struct node : peg::seq<affectation, peg::must<element>> {};
    struct full_node : peg::seq<indent, peg::star<multiline_comment>, node, peg::star<multiline_comment_block>, peg::opt<endline>> {};
    struct empty_line : peg::seq<peg::star<peg::blank>, peg::eol> {};
    struct block : peg::sor<empty_line, inline_comment, multiline_comment_block, full_node> {};
    struct vili_grammar : peg::until<peg::eof, peg::must<block>> {};
    struct grammar : peg::must<vili_grammar> {};
    // clang-format on
}