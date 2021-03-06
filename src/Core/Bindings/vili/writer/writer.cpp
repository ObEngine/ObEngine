#include <Bindings/vili/writer/writer.hpp>

#include <vili/writer.hpp>

#include <Bindings/Config.hpp>

namespace vili::writer::Bindings
{
    void LoadEnumDelimiterNewlinePolicy(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.new_enum<vili::writer::delimiter_newline_policy>(
            "delimiter_newline_policy",
            { { "never", vili::writer::delimiter_newline_policy::never },
                { "only_if_multiline",
                    vili::writer::delimiter_newline_policy::only_if_multiline },
                { "always", vili::writer::delimiter_newline_policy::always } });
    }
    void LoadEnumCommaSpacingPolicy(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.new_enum<vili::writer::comma_spacing_policy>(
            "comma_spacing_policy",
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
    void LoadFunctionDumpInteger(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_integer", vili::writer::dump_integer);
    }
    void LoadFunctionDumpNumber(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_number", vili::writer::dump_number);
    }
    void LoadFunctionDumpBoolean(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_boolean", vili::writer::dump_boolean);
    }
    void LoadFunctionDumpString(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_string", vili::writer::dump_string);
    }
    void LoadFunctionDumpArray(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_array", vili::writer::dump_array);
    }
    void LoadFunctionDumpObject(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump_object", vili::writer::dump_object);
    }
    void LoadFunctionDump(sol::state_view state)
    {
        sol::table writerNamespace = state["vili"]["writer"].get<sol::table>();
        writerNamespace.set_function("dump", vili::writer::dump);
    }
};