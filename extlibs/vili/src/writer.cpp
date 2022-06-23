#include <array>
#ifdef __cpp_lib_to_chars
#include <charconv>
#endif
#include <string>
#include <string_view>

#include <vili/writer.hpp>

namespace vili::writer
{
    dump_state make_child_state(const dump_state& state, bool in_array = false)
    {
        return dump_state {
            false,
            state.depth + 1,
            (in_array || state.object_mode == object_style::braces ) ?
                object_style::braces
                : object_style::indent
        };
    }

#ifdef __cpp_lib_to_chars
    std::string dump_integer(const vili::node& data)
    {
        if (!data.is<vili::integer>())
        {
            throw exceptions::invalid_cast(
                vili::integer_typename, vili::to_string(data.type()), VILI_EXC_INFO);
        }

        const vili::integer integer_value = data.as<vili::integer>();
        std::array<char, 20> result {};

        if (auto [ptr, ec]
            = std::to_chars(result.data(), result.data() + result.size(), integer_value);
            ec == std::errc())
        {
            return std::string(result.data(), ptr);
        }
        throw exceptions::integer_dump_error(integer_value, VILI_EXC_INFO);
    }

    std::string dump_number(const vili::node& data)
    {
        if (!data.is<vili::number>())
        {
            throw exceptions::invalid_cast(
                vili::number_typename, vili::to_string(data.type()), VILI_EXC_INFO);
        }

        const vili::number number_value = data.as<vili::number>();
        std::array<char, 45> result {};

        if (auto [ptr, ec]
            = std::to_chars(result.data(), result.data() + result.size(), number_value);
            ec == std::errc())
        {
            std::string number_as_string(result.data(), ptr);
            if (number_as_string.find('.') == std::string::npos)
            {
                number_as_string += ".0";
            }
            return utils::string::truncate_float(number_as_string);
        }
        throw exceptions::number_dump_error(number_value, VILI_EXC_INFO);
    }
#else
    std::string dump_integer(const vili::node& data)
    {
        if (!data.is<vili::integer>())
        {
            throw exceptions::invalid_cast(
                vili::integer_typename, vili::to_string(data.type()), VILI_EXC_INFO);
        }

        const vili::integer integer_value = data.as<vili::integer>();
        return std::to_string(integer_value);
    }

    std::string dump_number(const vili::node& data)
    {
        if (!data.is<vili::number>())
        {
            throw exceptions::invalid_cast(
                vili::number_typename, vili::to_string(data.type()), VILI_EXC_INFO);
        }

        const vili::number number_value = data.as<vili::number>();
        return std::to_string(number_value);
    }
#endif

    std::string dump_boolean(const vili::node& data)
    {
        if (!data.is<vili::boolean>())
        {
            throw exceptions::invalid_cast(
                vili::boolean_typename, vili::to_string(data.type()), VILI_EXC_INFO);
        }
        return (data.as<boolean>() ? "true" : "false");
    }

    std::string dump_string(const vili::node& data)
    {
        if (!data.is<vili::string>())
        {
            throw exceptions::invalid_cast(
                vili::string_typename, vili::to_string(data.type()), VILI_EXC_INFO);
        }
        return utils::string::quote(data.as<string>());
    }

    /**
     * \return true if items amount has been exceeded
     */
    inline bool check_max_items_per_line(
        unsigned int max_items_per_line, unsigned int items_count)
    {
        return !(!max_items_per_line
            || (max_items_per_line && items_count <= max_items_per_line));
    }

    /**
     * \return true if line length has been exceeded
     */
    inline bool check_max_line_length(size_t max_line_length, size_t line_length)
    {
        return !(!max_line_length || (max_line_length && line_length <= max_line_length));
    }

    inline bool should_insert_newline_next_to_brackets(
        const delimiter_newline_policy current_bracket,
        const delimiter_newline_policy opposite_bracket, const bool fits_on_single_line)
    {
        return (current_bracket == delimiter_newline_policy::always
            || current_bracket == delimiter_newline_policy::only_if_multiline
                && (!fits_on_single_line
                    || opposite_bracket == delimiter_newline_policy::always));
    }

    struct dumped_item
    {
        std::string dump;
        vili::node_type node_type;
    };

    std::string dump_array(const vili::node& data, const dump_options& options, const dump_state state)
    {
        if (!data.is<vili::array>())
        {
            throw exceptions::invalid_cast(
                vili::array_typename, vili::to_string(data.type()), VILI_EXC_INFO);
        }

        std::string dump_value = "[";
        bool must_indent = false;
        unsigned int items_per_line = 0;
        std::string current_line;

        std::vector<dumped_item> values_dumps;
        values_dumps.reserve(data.size());
        unsigned int total_content_length = 0;

        // Counters to check whether we exceed the items per line limit
        unsigned int primitive_items_counter = 0;
        unsigned int array_items_counter = 0;
        unsigned int object_items_counter = 0;
        bool no_children_with_newlines = true;
        for (const vili::node& item : data.as_array())
        {
            const std::string item_dump
                = dump(item, options, make_child_state(state, true));
            if (item_dump.find("\n") != std::string::npos)
            {
                no_children_with_newlines = false;
            }
            total_content_length += item_dump.size();
            // Spacing + comma
            total_content_length
                += options.array.inline_spacing + 1;
            values_dumps.push_back(dumped_item { item_dump, item.type() });
            if (item.is_primitive())
            {
                primitive_items_counter++;
            }
            else if (item.is_array())
            {
                array_items_counter++;
            }
            else if (item.is_object())
            {
                object_items_counter++;
            }
        }
        // We check item limits for each type (primitives, arrays, objects)
        bool max_primitives_per_line_exceeded = check_max_items_per_line(
            options.array.items_per_line.primitives, primitive_items_counter);
        bool max_arrays_per_line_exceeded = check_max_items_per_line(
            options.array.items_per_line.arrays, array_items_counter);
        bool max_objects_per_line_exceeded = check_max_items_per_line(
            options.array.items_per_line.objects, object_items_counter);
        // But also for any type
        bool max_items_per_line_exceeded = check_max_items_per_line(
            options.array.items_per_line.any, values_dumps.size());
        // We check if any of the limit has been exceeded
        const bool max_items_per_line_constraint_exceeded
            = (max_primitives_per_line_exceeded || max_arrays_per_line_exceeded
                || max_objects_per_line_exceeded || max_items_per_line_exceeded);

        bool max_line_length_exceeded
            = check_max_line_length(options.array.max_line_length, total_content_length);
        const bool fits_on_single_line = (!max_items_per_line_constraint_exceeded
            && !max_line_length_exceeded && no_children_with_newlines);
        if (should_insert_newline_next_to_brackets(options.array.starts_with_newline,
                options.array.ends_with_newline, fits_on_single_line))
        {
            dump_value += "\n";
            must_indent = true;
        }

        // We reset counters to re-use them while writing dumped values to string
        primitive_items_counter = 0;
        array_items_counter = 0;
        object_items_counter = 0;
        for (auto it = values_dumps.begin(); it != values_dumps.end(); ++it)
        {
            dumped_item& current_value_dump = *it;

            if (must_indent)
            {
                // If we are exporting a root array (not encapsulated in any object, dump the array with one indent)
                unsigned int root_array_indentation = (state.root ? 1 : 0);
                current_line += std::string(
                    options.indent * (state.depth + root_array_indentation), ' ');
            }

            must_indent = false;

            current_line += current_value_dump.dump;

            if (current_value_dump.node_type == node_type::array)
            {
                array_items_counter++;
            }
            else if (current_value_dump.node_type == node_type::object)
            {
                object_items_counter++;
            }
            else
            {
                primitive_items_counter++;
            }
            if (it != (values_dumps.end() - 1))
            {
                items_per_line++;
                // We check whether we have too much items of each type per line
                max_primitives_per_line_exceeded
                    = (options.array.items_per_line.primitives
                        && primitive_items_counter
                            >= options.array.items_per_line.primitives);
                max_arrays_per_line_exceeded = (options.array.items_per_line.arrays
                    && array_items_counter >= options.array.items_per_line.arrays);
                max_objects_per_line_exceeded = (options.array.items_per_line.objects
                    && object_items_counter >= options.array.items_per_line.objects);

                max_items_per_line_exceeded
                    = (options.array.items_per_line.any
                          && items_per_line >= options.array.items_per_line.any)
                    || (max_primitives_per_line_exceeded || max_arrays_per_line_exceeded
                        || max_objects_per_line_exceeded);
                max_line_length_exceeded = (options.array.max_line_length
                    && current_line.size() >= options.array.max_line_length);
                if (max_items_per_line_exceeded || max_line_length_exceeded)
                {
                    dump_value += current_line;
                    current_line.clear();
                    dump_value += ",\n";
                    items_per_line = 0;
                    must_indent = true;
                }
                else
                {
                    current_line += "," + std::string(options.array.inline_spacing, ' ');
                }
            }
        }
        dump_value += current_line;
        if (should_insert_newline_next_to_brackets(options.array.ends_with_newline,
                options.array.starts_with_newline, fits_on_single_line))
        {
            dump_value += "\n";
        }
        dump_value += "]";
        return dump_value;
    }

    std::string dump_object(
        const vili::node& data, const dump_options& options, const dump_state state)
    {
        if (!data.is<vili::object>())
        {
            throw exceptions::invalid_cast(
                vili::object_typename, vili::to_string(data.type()), VILI_EXC_INFO);
        }

        // Variables
        const vili::object& object_value = data.as<vili::object>();
        std::string dump_value;
        size_t index = 0;
        const size_t max_size = data.size();
        bool must_indent = false;
        std::string current_line;
        const bool bracket_style
            = (!state.root && (options.object.style == object_style::braces || state.object_mode == object_style::braces));

        // Opening brace if not root and bracket-style
        if (bracket_style)
        {
            dump_value = "{";
        }

        // Pre-dumping all items to check length
        std::unordered_map<std::string, dumped_item> values_dumps;
        values_dumps.reserve(data.size());
        unsigned int total_content_length = 0;
        // Colon + space after it
        const unsigned int base_required_space = 2;
        for (const auto& [key, value] : data.items())
        {
            const std::string item_dump = dump(value, options, make_child_state(state));
            total_content_length += base_required_space + key.size() + item_dump.size();
            // Whenever we use braces, length will be increased because of the commas and spaces around it
            if (options.object.style == object_style::braces)
            {
                total_content_length += options.object.inline_spacing + 1;
            }

            values_dumps.emplace(key, dumped_item { item_dump, value.type() });
        }

        // Checking if everything can fit in a single line based on constraints
        const bool fits_all_items_in_single_line = !check_max_items_per_line(
            options.object.items_per_line.any, values_dumps.size());
        const bool fits_total_length_in_single_line
            = !check_max_line_length(options.object.max_line_length, total_content_length);
        const bool fits_on_single_line
            = (fits_all_items_in_single_line && fits_total_length_in_single_line);

        if (!state.root
            && (should_insert_newline_next_to_brackets(options.array.starts_with_newline,
                    options.array.ends_with_newline, fits_on_single_line)
                || !bracket_style))
        {
            dump_value += "\n";
            must_indent = true;
        }

        // Dumping each key: value
        std::size_t iteration_index = 0;
        std::size_t object_size = data.size();
        unsigned int items_per_line = 0;
        for (const auto& [key, value] : data.items())
        {
            dumped_item current_value_dump = values_dumps[key];
            if (!value.is_null())
            {
                if (must_indent)
                {
                    current_line += std::string(options.indent * state.depth, ' ');
                }
                must_indent = false;
                current_line += key;
                current_line += ":";
                // Don't put a space in case we dump an indent-based object (avoid trailing spaces)
                if (!(value.is_object() && options.object.style == object_style::indent))
                {
                    current_line += ' ';
                }

                current_line += current_value_dump.dump;
            }
            items_per_line++;
            const bool max_items_per_line_exceeded = (options.object.items_per_line.any
                && items_per_line >= options.object.items_per_line.any);
            const bool max_line_length_exceeded = (options.object.max_line_length
                && current_line.size() >= options.object.max_line_length);
            const bool must_break_line
                = max_items_per_line_exceeded || max_line_length_exceeded;
            // For bracket style, the object must be indented twice : whole object (by the parent) and each key (by current object)
            if (bracket_style && (must_break_line || must_indent))
            {
                // current_line = std::string(options.indent, ' ') + current_line;
            }
            if (iteration_index != object_size - 1)
            {
                if (must_break_line || !bracket_style)
                {
                    dump_value += current_line;
                    current_line.clear();
                    if (bracket_style)
                    {
                        dump_value += ",\n";
                        must_indent = true;
                    }
                    else
                    {
                        dump_value += "\n";
                        must_indent = true;
                        // Newlines after objects
                        if (current_value_dump.node_type == node_type::object)
                        {
                            current_line += std::string(
                                options.object.objects_vertical_spacing, '\n');
                        }
                        // Newlines after arrays
                        else if (current_value_dump.node_type == node_type::array)
                        {
                            current_line += std::string(
                                options.object.arrays_vertical_spacing, '\n');
                        }
                    }
                    items_per_line = 0;
                }
                else if (bracket_style)
                {
                    current_line += ", ";
                }
            }
            iteration_index++;
        }

        dump_value += current_line;

        if (bracket_style)
        {
            if (should_insert_newline_next_to_brackets(options.object.ends_with_newline,
                    options.object.starts_with_newline, fits_on_single_line))
            {
                dump_value += "\n";
            }
            dump_value += std::string(options.indent * (state.depth - 1), ' ');
            dump_value += "}";
        }

        return dump_value;
    }

    std::string dump(const vili::node& data, const dump_options& options, const dump_state state)
    {
        if (data.is<vili::integer>())
        {
            return dump_integer(data);
        }
        else if (data.is<vili::number>())
        {
            return dump_number(data);
        }
        else if (data.is<vili::boolean>())
        {
            return dump_boolean(data);
        }
        else if (data.is<vili::string>())
        {
            return dump_string(data);
        }
        else if (data.is<vili::array>())
        {
            return dump_array(data, options, state);
        }
        else if (data.is<vili::object>())
        {
            return dump_object(data, options, state);
        }
        else
        {
            throw exceptions::invalid_node_type(
                vili::to_string(data.type()), VILI_EXC_INFO);
        }
    }
}
