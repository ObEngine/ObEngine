#pragma once

#include <tao/pegtl.hpp>

namespace vili::parser::rules
{
    namespace peg = tao::pegtl;
    // clang-format off
    struct identifier : peg::identifier {};
    struct indent : peg::seq<peg::bol, peg::star<peg::blank>> {};
    struct affectation : peg::seq<identifier, peg::pad<peg::one<':'>, peg::blank>> {};

    // String
    struct string_content : peg::star<peg::not_one<'"'>> {};
    struct string : peg::seq<peg::one<'"'>, string_content, peg::one<'"'>> {};

    // Booleans
    struct true_ : peg::string<'t', 'r', 'u', 'e'> {};
    struct false_ : peg::string<'f', 'a', 'l', 's', 'e'> {};
    struct boolean : peg::sor<true_, false_> {};

    // Numbers
    struct sign : peg::one<'+', '-'> {};
    struct integer : peg::seq<peg::opt<sign>, peg::plus<peg::digit>> {};
    struct number : peg::seq<peg::opt<sign>, peg::star<peg::digit>, peg::one<'.'>, peg::plus<peg::digit>> {};

    // Data
    struct data : peg::sor<boolean, number, integer, string> {};
    struct brace_based_object;
    struct array;
    struct object;
    struct template_usage;
    struct inline_element : peg::sor<boolean, number, integer, string, array, brace_based_object, template_usage> {};
    struct inline_node : peg::seq<affectation, inline_element> {};
    struct element : peg::sor<data, array, object, template_usage> {};

    // Arrays
    struct array_elements : peg::list<inline_element, peg::one<','>, peg::space> {};
    struct open_array : peg::one<'['> {};
    struct close_array : peg::one<']'> {};
    struct array : peg::seq<open_array, peg::pad_opt<array_elements, peg::space>, close_array> {};

    // Objects
    struct node;
    struct indent_based_object : peg::eol {};
    struct open_object : peg::one<'{'> {};
    struct close_object : peg::one<'}'> {};
    struct comma_or_newline : peg::seq<peg::pad<peg::sor<peg::one<','>, peg::eol>, peg::space>, peg::star<peg::space>> {};
    struct object_elements : peg::list<inline_node, comma_or_newline> {};
    struct brace_based_object : peg::seq<open_object, peg::pad_opt<object_elements, peg::space>, close_object> {};
    struct object : peg::sor<brace_based_object, indent_based_object> {};

    // Comments
    struct inline_comment : peg::seq<peg::one<'#'>, peg::until<peg::eol, peg::any>> {};

    // Templates
    struct template_keyword : peg::string<'t', 'e', 'm', 'p', 'l', 'a', 't', 'e'> {};
    struct template_decl : peg::seq<peg::bol, template_keyword, peg::blank, affectation, data> {}; // TODO: Include complex types
    struct template_usage : peg::identifier {};

    // Nodes
    struct node : peg::seq<affectation, element> {};
    struct full_node : peg::seq<indent, node, peg::opt<peg::eol>> {};
    struct empty_line : peg::seq<peg::star<peg::blank>, peg::eol> {};
    struct line : peg::sor<empty_line, inline_comment, template_decl, full_node> {};
    struct grammar : peg::until<peg::eof, peg::must<line>> {};
    // clang-format on
}