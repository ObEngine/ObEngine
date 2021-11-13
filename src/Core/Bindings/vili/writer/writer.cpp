#include <Bindings/vili/writer/writer.hpp>

#include <vili/writer.hpp>

#include <Bindings/Config.hpp>

namespace vili::writer::Bindings
{
    void LoadEnumDelimiterNewlinePolicy(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.new_enum<vili::writer::delimiter_newline_policy>("delimiter_newline_policy",
            { { "never", vili::writer::delimiter_newline_policy::never },
                { "only_if_multiline", vili::writer::delimiter_newline_policy::only_if_multiline },
                { "always", vili::writer::delimiter_newline_policy::always } });
    }
    void LoadEnumCommaSpacingPolicy(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.new_enum<vili::writer::comma_spacing_policy>("comma_spacing_policy",
            { { "left_side", vili::writer::comma_spacing_policy::left_side },
                { "right_side", vili::writer::comma_spacing_policy::right_side },
                { "both", vili::writer::comma_spacing_policy::both } });
    }
    void LoadEnumObjectStyle(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.new_enum<vili::writer::object_style>("object_style",
            { { "braces", vili::writer::object_style::braces },
                { "indent", vili::writer::object_style::indent } });
    }
    void LoadClassDumpOptions(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        sol::usertype<vili::writer::dump_options> binddump_options
            = writerNamespace.new_usertype<vili::writer::dump_options>(
                "dump_options", sol::call_constructor, sol::default_constructor);
        binddump_options["indent"] = &vili::writer::dump_options::indent;
        binddump_options["array"] = &vili::writer::dump_options::array;
        binddump_options["object"] = &vili::writer::dump_options::object;
        binddump_options["root"] = &vili::writer::dump_options::root;
    }
    void LoadClass_array(sol::state_view state)
    {
        sol::table dump_optionsNamespace
            = state["vili"]["writer"]["dump_options"].get<sol::table>();
        sol::usertype<vili::writer::dump_options::_array> bind_array
            = dump_optionsNamespace.new_usertype<vili::writer::dump_options::_array>(
                "_array", sol::call_constructor, sol::default_constructor);
        bind_array["items_per_line"] = &vili::writer::dump_options::_array::items_per_line;
        bind_array["max_line_length"] = &vili::writer::dump_options::_array::max_line_length;
        bind_array["starts_with_newline"]
            = &vili::writer::dump_options::_array::starts_with_newline;
        bind_array["ends_with_newline"] = &vili::writer::dump_options::_array::ends_with_newline;
        bind_array["left_bracket_spacing"]
            = &vili::writer::dump_options::_array::left_bracket_spacing;
        bind_array["right_bracket_spacing"]
            = &vili::writer::dump_options::_array::right_bracket_spacing;
        bind_array["inline_spacing"] = &vili::writer::dump_options::_array::inline_spacing;
        bind_array["comma_spacing"] = &vili::writer::dump_options::_array::comma_spacing;
    }
    void LoadClass_object(sol::state_view state)
    {
        sol::table dump_optionsNamespace
            = state["vili"]["writer"]["dump_options"].get<sol::table>();
        sol::usertype<vili::writer::dump_options::_object> bind_object
            = dump_optionsNamespace.new_usertype<vili::writer::dump_options::_object>(
                "_object", sol::call_constructor, sol::default_constructor);
        bind_object["items_per_line"] = &vili::writer::dump_options::_object::items_per_line;
        bind_object["max_line_length"] = &vili::writer::dump_options::_object::max_line_length;
        bind_object["starts_with_newline"]
            = &vili::writer::dump_options::_object::starts_with_newline;
        bind_object["ends_with_newline"] = &vili::writer::dump_options::_object::ends_with_newline;
        bind_object["left_brace_spacing"]
            = &vili::writer::dump_options::_object::left_brace_spacing;
        bind_object["right_brace_spacing"]
            = &vili::writer::dump_options::_object::right_brace_spacing;
        bind_object["affectation_left_spaces"]
            = &vili::writer::dump_options::_object::affectation_left_spaces;
        bind_object["affectation_right_spaces"]
            = &vili::writer::dump_options::_object::affectation_right_spaces;
        bind_object["inline_spacing"] = &vili::writer::dump_options::_object::inline_spacing;
        bind_object["comma_spacing"] = &vili::writer::dump_options::_object::comma_spacing;
        bind_object["style"] = &vili::writer::dump_options::_object::style;
    }
    void LoadFunctionDumpInteger(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_integer", &vili::writer::dump_integer);
    }
    void LoadFunctionDumpNumber(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_number", &vili::writer::dump_number);
    }
    void LoadFunctionDumpBoolean(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_boolean", &vili::writer::dump_boolean);
    }
    void LoadFunctionDumpString(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_string", &vili::writer::dump_string);
    }
    void LoadFunctionDumpArray(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_array",
            sol::overload([](const vili::node& data) -> std::string
                { return vili::writer::dump_array(data); },
                [](const vili::node& data, const vili::writer::dump_options& options) -> std::string
                { return vili::writer::dump_array(data, options); }));
    }
    void LoadFunctionDumpObject(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_object",
            sol::overload([](const vili::node& data) -> std::string
                { return vili::writer::dump_object(data); },
                [](const vili::node& data, const vili::writer::dump_options& options) -> std::string
                { return vili::writer::dump_object(data, options); }));
    }
    void LoadFunctionDump(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump",
            sol::overload([](const vili::node& data) -> std::string
                { return vili::writer::dump(data); },
                [](const vili::node& data, const vili::writer::dump_options& options) -> std::string
                { return vili::writer::dump(data, options); }));
    }
};