#pragma once

#include <tao/pegtl.hpp>

#include <vili/parser/grammar.hpp>

namespace vili::parser
{
    /**
     * \nobind
     * \brief Base error message
     */
    template <typename> inline constexpr const char* error_message = nullptr;

    /**
     * \nobind
     * \brief Message that will be printed when the parser
     *        does not find an expected affectation operator
     */
    template <>
    inline constexpr auto
        error_message<rules::affectation_separator> = "invalid affectation, expected ':'";

    // String
    /**
     * \nobind
     * \brief Message that will be printed when the parser
     *        does not found digits after unicode character
     */
    template <>
    inline constexpr auto
        error_message<rules::xdigit> = "incomplete universal character name";
    /**
     * \nobind
     * \brief Message that will be printed when the parser
     *        find an incorrect escape sequence
     */
    template <>
    inline constexpr auto error_message<rules::escaped> = "unknown escape sequence";
    /**
     * \nobind
     * \brief Message that will be printed when the parser
     *        find an incorrect character in a vili string
     */
    template <>
    inline constexpr auto
        error_message<rules::char_> = "invalid character in vili string";
    /**
     * \nobind
     * \brief Message that will be printed when the parser
     *        find an unterminated string
     */
    template <>
    inline constexpr auto
        error_message<rules::string_content> = "unterminated string, expected '\"'";

    // Data
    /**
     * \nobind
     * \brief Message that will be printed when the parser
     *        does not find an expected inline_element
     */
    template <>
    inline constexpr auto
        error_message<rules::inline_element> = "invalid vili inline element";
    /**
     * \nobind
     * \brief Message that will be printed when the parser
     *        does not find an expected inline node
     */
    template <>
    inline constexpr auto error_message<rules::inline_node> = "invalid vili inline node";
    /**
     * \nobind
     * \brief Message that will be printed when the parser
     *        does not find an expected vili element
     */
    template <>
    inline constexpr auto error_message<rules::element> = "invalid vili element";

    // Arrays
    /**
     * \nobind
     * \brief Message that will be printed when the parser
     *        find an unclosed array
     */
    template <>
    inline constexpr auto
        error_message<rules::close_array> = "unclosed vili array, expected ']'";

    // Objects
    /**
     * \nobind
     * \brief Message that will be printed when the parser
     *        find an unclosed object
     */
    template <>
    inline constexpr auto
        error_message<rules::close_object> = "unclosed vili object, expected '}'";

    // Nodes
    /**
     * \nobind
     * \brief Message that will be printed when the parser
     *        find an invalid block
     */
    template <> inline constexpr auto error_message<rules::block> = "invalid block";
    /**
     * \nobind
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