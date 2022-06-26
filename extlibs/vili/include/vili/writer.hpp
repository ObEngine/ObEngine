#include <vili/node.hpp>

namespace vili::writer
{
    enum class delimiter_newline_policy
    {
        never,
        only_if_multiline,
        always
    };
    enum class object_style
    {
        braces,
        indent
    };
    struct dump_options
    {
        struct _items_per_line
        {
            unsigned int any = 0;
            unsigned int primitives = 0;
            unsigned int arrays = 1;
            unsigned int objects = 1;
        };

        unsigned int indent = 4;
        struct _array
        {
            _items_per_line items_per_line;
            unsigned int max_line_length = 80;
            delimiter_newline_policy starts_with_newline
                = delimiter_newline_policy::only_if_multiline;
            delimiter_newline_policy ends_with_newline
                = delimiter_newline_policy::only_if_multiline;
            unsigned int inline_spacing = 1;
        };
        _array array;

        struct _object
        {
            _items_per_line items_per_line { 1, 1, 1, 1 };
            unsigned int max_line_length = 80;
            delimiter_newline_policy starts_with_newline
                = delimiter_newline_policy::only_if_multiline;
            delimiter_newline_policy ends_with_newline
                = delimiter_newline_policy::only_if_multiline;
            unsigned int inline_spacing = 1;
            unsigned int arrays_vertical_spacing = 0;
            unsigned int objects_vertical_spacing = 1;
            object_style style = object_style::indent;
        };
        _object object;
    };

    struct dump_state
    {
        bool root = true;
        unsigned depth = 0;
        object_style object_mode = object_style::indent;
    };

    std::string dump_integer(const vili::node& data);
    std::string dump_number(const vili::node& data);
    std::string dump_boolean(const vili::node& data);
    std::string dump_string(const vili::node& data);
    std::string dump_array(const vili::node& data,
        const dump_options& options, dump_state state);
    std::string dump_object(const vili::node& data,
        const dump_options& options, dump_state state);
    std::string dump(const vili::node& data,
        const dump_options& options = dump_options {}, dump_state state = dump_state {});
}