#pragma once

#include <tao/pegtl.hpp>

#include <vili/parser/grammar.hpp>

namespace vili::parser
{
    /**
     * \brief Base error message
     */
    template <typename> inline constexpr const char* error_message = nullptr;

    /**
     * \brief Message that will be printed when the parser
     *        does not find an expected affectation operator
     */
    template <>
    inline constexpr auto
        error_message<rules::affectation_separator> = "invalid affectation, expected ':'";

    // String
    /**
     * \brief Message that will be printed when the parser
     *        does not found digits after unicode character
     */
    template <>
    inline constexpr auto
        error_message<rules::xdigit> = "incomplete universal character name";
    /**
     * \brief Message that will be printed when the parser
     *        find an incorrect escape sequence
     */
    template <>
    inline constexpr auto error_message<rules::escaped> = "unknown escape sequence";
    /**
     * \brief Message that will be printed when the parser
     *        find an incorrect character in a vili string
     */
    template <>
    inline constexpr auto
        error_message<rules::char_> = "invalid character in vili string";
    /**
     * \brief Message that will be printed when the parser
     *        find an unterminated string
     */
    template <>
    inline constexpr auto
        error_message<rules::string_content> = "unterminated string, expected '\"'";

    // Data
    /**
     * \brief Message that will be printed when the parser
     *        does not find an expected inline_element
     */
    template <>
    inline constexpr auto
        error_message<rules::inline_element> = "invalid vili inline element";
    /**
     * \brief Message that will be printed when the parser
     *        does not find an expected inline node
     */
    template <>
    inline constexpr auto error_message<rules::inline_node> = "invalid vili inline node";
    /**
     * \brief Message that will be printed when the parser
     *        does not find an expected vili element
     */
    template <>
    inline constexpr auto error_message<rules::element> = "invalid vili element";

    // Arrays
    /**
     * \brief Message that will be printed when the parser
     *        find an unclosed array
     */
    template <>
    inline constexpr auto
        error_message<rules::close_array> = "unclosed vili array, expected ']'";

    // Objects
    /**
     * \brief Message that will be printed when the parser
     *        find an unclosed object
     */
    template <>
    inline constexpr auto
        error_message<rules::close_object> = "unclosed vili object, expected '}'";

    // Nodes
    /**
     * \brief Message that will be printed when the parser
     *        find an invalid block
     */
    template <> inline constexpr auto error_message<rules::block> = "invalid block";
    /**
     * \brief Message that will be printed when the parser
     *        does find an invalid vili content
     */
    template <>
    inline constexpr auto error_message<rules::vili_grammar> = "invalid vili content";

    struct error
    {
        template <typename Rule> static constexpr auto raise_on_failure = false;
        template <typename Rule> static constexpr auto message = error_message<Rule>;
    };

    template <typename Rule> using control = tao::pegtl::must_if<error>::control<Rule>;
}