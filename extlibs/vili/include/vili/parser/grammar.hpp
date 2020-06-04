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
    struct template_usage;
    struct inline_element : peg::sor<boolean, number, integer, string, array, brace_based_object, template_usage> {};
    struct inline_node : peg::seq<affectation, inline_element> {};
    struct element : peg::sor<data, array, object, template_usage> {};

    // Arrays
    struct array_separator : peg::one<','> {};
    struct array_elements : peg::list_must<inline_element, array_separator, peg::space> {};
    struct open_array : peg::one<'['> {};
    struct close_array : peg::one<']'> {};
    struct array : peg::seq<open_array, peg::pad_opt<array_elements, peg::space>, peg::must<close_array>> {};

    // Objects
    struct node;
    struct indent_based_object : peg::eol {};
    struct open_object : peg::one<'{'> {};
    struct close_object : peg::one<'}'> {};
    struct comma_or_newline : peg::pad<peg::sor<peg::one<','>, peg::eol>, peg::space> {};
    struct object_elements : peg::list_must<inline_node, comma_or_newline> {};
    struct brace_based_object : peg::seq<open_object, peg::pad_opt<object_elements, peg::space>, peg::must<close_object>> {};
    struct object : peg::sor<brace_based_object, indent_based_object> {};

    // Comments
    struct inline_comment : peg::seq<peg::one<'#'>, peg::until<peg::eol, peg::any>> {};

    // Templates
    struct template_keyword : peg::string<'t', 'e', 'm', 'p', 'l', 'a', 't', 'e'> {};
    struct template_identifier : peg::identifier {};
    struct template_decl_content : peg::seq<peg::blank, template_identifier, peg::pad<peg::one<':'>, peg::blank>, inline_element> {};
    struct template_begin : peg::seq<peg::bol, template_keyword> {};
    struct template_decl : peg::if_must<template_begin, template_decl_content> {};
    struct template_identifier_usage : template_identifier {};
    struct template_specialization : peg::sor<array, brace_based_object> {};
    struct template_usage : peg::seq<template_identifier_usage, peg::opt<peg::seq<peg::star<peg::blank>, template_specialization>>> {};

    // Nodes
    struct node : peg::seq<affectation, peg::must<element>> {};
    struct full_node : peg::seq<indent, node, peg::opt<peg::eol>> {};
    struct empty_line : peg::seq<peg::star<peg::blank>, peg::eol> {};
    struct line : peg::sor<empty_line, inline_comment, template_decl, full_node> {};
    struct vili_grammar : peg::until<peg::eof, peg::must<line>> {};
    struct grammar : peg::must<vili_grammar> {};
    // clang-format on
}