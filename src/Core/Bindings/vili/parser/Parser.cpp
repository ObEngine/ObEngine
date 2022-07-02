#include <Bindings/vili/parser/Parser.hpp>

#include <Bindings/Patches.hpp>
#include <vili/parser.hpp>
#include <vili/parser/parser_state.hpp>

#include <Bindings/Config.hpp>

namespace vili::parser::bindings
{
    void load_class_node_in_stack(sol::state_view state)
    {
        sol::table parser_namespace = state["vili"]["parser"].get<sol::table>();
        sol::usertype<vili::parser::node_in_stack> bind_node_in_stack
            = parser_namespace.new_usertype<vili::parser::node_in_stack>("node_in_stack",
                sol::call_constructor,
                sol::constructors<vili::parser::node_in_stack(vili::node*, int)>());
        bind_node_in_stack["item"] = &vili::parser::node_in_stack::item;
        bind_node_in_stack["indent"] = &vili::parser::node_in_stack::indent;
    }
    void load_class_state(sol::state_view state)
    {
        sol::table parser_namespace = state["vili"]["parser"].get<sol::table>();
        sol::usertype<vili::parser::state> bind_state
            = parser_namespace.new_usertype<vili::parser::state>("state", sol::call_constructor,
                sol::constructors<vili::parser::state(),
                    vili::parser::state(const vili::parser::state&)>());
        bind_state["set_indent"] = &vili::parser::state::set_indent;
        bind_state["use_indent"] = &vili::parser::state::use_indent;
        bind_state["set_active_identifier"] = &vili::parser::state::set_active_identifier;
        bind_state["open_block"] = &vili::parser::state::open_block;
        bind_state["close_block"] = &vili::parser::state::close_block;
        bind_state["push"] = &vili::parser::state_push_proxy;
        bind_state["root"] = &vili::parser::state::root;
    }
    void load_function_from_string(sol::state_view state)
    {
        sol::table parser_namespace = state["vili"]["parser"].get<sol::table>();
        parser_namespace.set_function("from_string",
            sol::overload(
                [](std::string_view data) -> vili::node { return vili::parser::from_string(data); },
                [](std::string_view data, vili::parser::state parser_state) -> vili::node {
                    return vili::parser::from_string(data, parser_state);
                }));
    }
    void load_function_from_file(sol::state_view state)
    {
        sol::table parser_namespace = state["vili"]["parser"].get<sol::table>();
        parser_namespace.set_function("from_file", &vili::parser::from_file);
    }
};