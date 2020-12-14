#include <vili/node.hpp>

namespace vili::writer
{
    enum class delimiter_newline_policy
    {
        never,
        only_if_multiline,
        always
    };
    enum class comma_spacing_policy
    {
        left_side,
        right_side,
        both
    };
    enum class object_style
    {
        braces,
        indent
    };
    struct dump_options
    {
        unsigned int indent = 4;
        struct array
        {
            unsigned int items_per_line = 0;
            unsigned int max_line_length = 0;
            delimiter_newline_policy starts_with_newline
                = delimiter_newline_policy::only_if_multiline;
            delimiter_newline_policy ends_with_newline
                = delimiter_newline_policy::only_if_multiline;
            unsigned int left_bracket_spacing = 0;
            unsigned int right_bracket_spacing = 0;
            unsigned int inline_spacing = 1;
            comma_spacing_policy comma_spacing = comma_spacing_policy::right_side;
        };
        array array;

        struct object
        {
            unsigned int items_per_line = 0;
            unsigned int max_line_length = 0;
            delimiter_newline_policy starts_with_newline
                = delimiter_newline_policy::only_if_multiline;
            delimiter_newline_policy ends_with_newline
                = delimiter_newline_policy::only_if_multiline;
            unsigned int left_brace_spacing = 0;
            unsigned int right_brace_spacing = 0;
            unsigned int affectation_left_spaces = 0;
            unsigned int affectation_right_spaces = 1;
            unsigned int inline_spacing = 1;
            comma_spacing_policy comma_spacing = comma_spacing_policy::right_side;
            object_style style = object_style::indent;
        };
        object object;

        bool root = true;
    };

    std::string dump_integer(const vili::node& data);
    std::string dump_number(const vili::node& data);
    std::string dump_boolean(const vili::node& data);
    std::string dump_string(const vili::node& data);
    std::string dump_array(
        const vili::node& data, const dump_options& options = dump_options {});
    std::string dump_object(
        const vili::node& data, const dump_options& options = dump_options {});
    std::string dump(
        const vili::node& data, const dump_options& options = dump_options {});
}