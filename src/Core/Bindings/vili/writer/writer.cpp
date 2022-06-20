#include <Bindings/vili/writer/Writer.hpp>

#include <vili/writer.hpp>

#include <Bindings/Config.hpp>

namespace vili::writer::bindings
{
    void load_enum_delimiter_newline_policy(sol::state_view state)
    {
        sol::table writer_namespace = state["vili"]["writer"].get<sol::table>();
        writer_namespace.new_enum<vili::writer::delimiter_newline_policy>(
            "delimiter_newline_policy",
            { { "never", vili::writer::delimiter_newline_policy::never },
                { "only_if_multiline", vili::writer::delimiter_newline_policy::only_if_multiline },
                { "always", vili::writer::delimiter_newline_policy::always } });
    }
    void load_enum_comma_spacing_policy(sol::state_view state)
    {
        sol::table writer_namespace = state["vili"]["writer"].get<sol::table>();
        writer_namespace.new_enum<vili::writer::comma_spacing_policy>("comma_spacing_policy",
            { { "left_side", vili::writer::comma_spacing_policy::left_side },
                { "right_side", vili::writer::comma_spacing_policy::right_side },
                { "both", vili::writer::comma_spacing_policy::both } });
    }
    void load_enum_object_style(sol::state_view state)
    {
        sol::table writer_namespace = state["vili"]["writer"].get<sol::table>();
        writer_namespace.new_enum<vili::writer::object_style>("object_style",
            { { "braces", vili::writer::object_style::braces },
                { "indent", vili::writer::object_style::indent } });
    }
    void load_class_dump_options(sol::state_view state)
    {
        sol::table writer_namespace = state["vili"]["writer"].get<sol::table>();
        sol::usertype<vili::writer::dump_options> bind_dump_options
            = writer_namespace.new_usertype<vili::writer::dump_options>(
                "dump_options", sol::call_constructor, sol::default_constructor);
        bind_dump_options["indent"] = &vili::writer::dump_options::indent;
        bind_dump_options["array"] = &vili::writer::dump_options::array;
        bind_dump_options["object"] = &vili::writer::dump_options::object;
        bind_dump_options["root"] = &vili::writer::dump_options::root;
    }
    void load_class__array(sol::state_view state)
    {
        sol::table dump_options_namespace
            = state["vili"]["writer"]["dump_options"].get<sol::table>();
        sol::usertype<vili::writer::dump_options::_array> bind__array
            = dump_options_namespace.new_usertype<vili::writer::dump_options::_array>(
                "_array", sol::call_constructor, sol::default_constructor);
        bind__array["items_per_line"] = &vili::writer::dump_options::_array::items_per_line;
        bind__array["max_line_length"] = &vili::writer::dump_options::_array::max_line_length;
        bind__array["starts_with_newline"]
            = &vili::writer::dump_options::_array::starts_with_newline;
        bind__array["ends_with_newline"] = &vili::writer::dump_options::_array::ends_with_newline;
        bind__array["left_bracket_spacing"]
            = &vili::writer::dump_options::_array::left_bracket_spacing;
        bind__array["right_bracket_spacing"]
            = &vili::writer::dump_options::_array::right_bracket_spacing;
        bind__array["inline_spacing"] = &vili::writer::dump_options::_array::inline_spacing;
        bind__array["comma_spacing"] = &vili::writer::dump_options::_array::comma_spacing;
    }
    void load_class__object(sol::state_view state)
    {
        sol::table dump_options_namespace
            = state["vili"]["writer"]["dump_options"].get<sol::table>();
        sol::usertype<vili::writer::dump_options::_object> bind__object
            = dump_options_namespace.new_usertype<vili::writer::dump_options::_object>(
                "_object", sol::call_constructor, sol::default_constructor);
        bind__object["items_per_line"] = &vili::writer::dump_options::_object::items_per_line;
        bind__object["max_line_length"] = &vili::writer::dump_options::_object::max_line_length;
        bind__object["starts_with_newline"]
            = &vili::writer::dump_options::_object::starts_with_newline;
        bind__object["ends_with_newline"] = &vili::writer::dump_options::_object::ends_with_newline;
        bind__object["left_brace_spacing"]
            = &vili::writer::dump_options::_object::left_brace_spacing;
        bind__object["right_brace_spacing"]
            = &vili::writer::dump_options::_object::right_brace_spacing;
        bind__object["affectation_left_spaces"]
            = &vili::writer::dump_options::_object::affectation_left_spaces;
        bind__object["affectation_right_spaces"]
            = &vili::writer::dump_options::_object::affectation_right_spaces;
        bind__object["inline_spacing"] = &vili::writer::dump_options::_object::inline_spacing;
        bind__object["comma_spacing"] = &vili::writer::dump_options::_object::comma_spacing;
        bind__object["style"] = &vili::writer::dump_options::_object::style;
    }
    void load_function_dump_integer(sol::state_view state)
    {
        sol::table writer_namespace = state["vili"]["writer"].get<sol::table>();
        writer_namespace.set_function("dump_integer", &vili::writer::dump_integer);
    }
    void load_function_dump_number(sol::state_view state)
    {
        sol::table writer_namespace = state["vili"]["writer"].get<sol::table>();
        writer_namespace.set_function("dump_number", &vili::writer::dump_number);
    }
    void load_function_dump_boolean(sol::state_view state)
    {
        sol::table writer_namespace = state["vili"]["writer"].get<sol::table>();
        writer_namespace.set_function("dump_boolean", &vili::writer::dump_boolean);
    }
    void load_function_dump_string(sol::state_view state)
    {
        sol::table writer_namespace = state["vili"]["writer"].get<sol::table>();
        writer_namespace.set_function("dump_string", &vili::writer::dump_string);
    }
    void load_function_dump_array(sol::state_view state)
    {
        sol::table writer_namespace = state["vili"]["writer"].get<sol::table>();
        writer_namespace.set_function("dump_array",
            sol::overload([](const vili::node& data)
                              -> std::string { return vili::writer::dump_array(data); },
                [](const vili::node& data, const vili::writer::dump_options& options)
                    -> std::string { return vili::writer::dump_array(data, options); }));
    }
    void load_function_dump_object(sol::state_view state)
    {
        sol::table writer_namespace = state["vili"]["writer"].get<sol::table>();
        writer_namespace.set_function("dump_object",
            sol::overload([](const vili::node& data)
                              -> std::string { return vili::writer::dump_object(data); },
                [](const vili::node& data, const vili::writer::dump_options& options)
                    -> std::string { return vili::writer::dump_object(data, options); }));
    }
    void load_function_dump(sol::state_view state)
    {
        sol::table writer_namespace = state["vili"]["writer"].get<sol::table>();
        writer_namespace.set_function("dump",
            sol::overload(
                [](const vili::node& data) -> std::string { return vili::writer::dump(data); },
                [](const vili::node& data, const vili::writer::dump_options& options)
                    -> std::string { return vili::writer::dump(data, options); }));
    }
};