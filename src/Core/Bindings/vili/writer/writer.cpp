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
        bind__array["inline_spacing"] = &vili::writer::dump_options::_array::inline_spacing;
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
        bind__object["inline_spacing"] = &vili::writer::dump_options::_object::inline_spacing;
        bind__object["style"] = &vili::writer::dump_options::_object::style;
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