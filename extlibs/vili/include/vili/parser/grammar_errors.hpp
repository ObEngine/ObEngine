#pragma once

#include <tao/pegtl.hpp>

#include <vili/parser/grammar.hpp>

namespace vili::parser
{
    template <typename> inline constexpr const char* error_message = nullptr;

    template <>
    inline constexpr auto
        error_message<rules::affectation_separator> = "invalid affectation, expected ':'";

    // String
    template <>
    inline constexpr auto
        error_message<rules::string_delimiter> = "unterminated string, expected '\"'";

    // Data
    template <>
    inline constexpr auto
        error_message<rules::inline_element> = "invalid vili inline element";
    template <>
    inline constexpr auto error_message<rules::inline_node> = "invalid vili inline node";
    template <>
    inline constexpr auto error_message<rules::element> = "invalid vili element";

    // Arrays
    template <>
    inline constexpr auto
        error_message<rules::close_array> = "unclosed vili array, expected ']'";

    // Objects
    template <>
    inline constexpr auto
        error_message<rules::close_object> = "unclosed vili object, expected '}'";

    // Templates
    template <>
    inline constexpr auto error_message<
        rules::template_decl_content> = "invalid template declaration, missing content";

    // Nodes
    template <> inline constexpr auto error_message<rules::line> = "invalid line";
    template <>
    inline constexpr auto error_message<rules::vili_grammar> = "invalid vili content";

    struct error
    {
        template <typename Rule> static constexpr auto raise_on_failure = false;
        template <typename Rule> static constexpr auto message = error_message<Rule>;
    };

    template <typename Rule> using control = tao::pegtl::must_if<error>::control<Rule>;
}