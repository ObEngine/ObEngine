#include <Bindings/vili/parser/parser.hpp>

#include <Bindings/Patches.hpp>
#include <vili/parser.hpp>
#include <vili/parser/grammar_errors.hpp>
#include <vili/parser/parser_state.hpp>

#include <Bindings/Config.hpp>

namespace vili::parser::Bindings
{
    void LoadClassNodeInStack(sol::state_view state)
    {
        sol::table parserNamespace = state["vili"]["parser"].get<sol::table>();
        sol::usertype<vili::parser::node_in_stack> bindnode_in_stack
            = parserNamespace.new_usertype<vili::parser::node_in_stack>("node_in_stack",
                sol::call_constructor,
                sol::constructors<vili::parser::node_in_stack(vili::node*, int)>());
        bindnode_in_stack["item"] = &vili::parser::node_in_stack::item;
        bindnode_in_stack["indent"] = &vili::parser::node_in_stack::indent;
    }
    void LoadClassState(sol::state_view state)
    {
        sol::table parserNamespace = state["vili"]["parser"].get<sol::table>();
        sol::usertype<vili::parser::state> bindstate
            = parserNamespace.new_usertype<vili::parser::state>("state", sol::call_constructor,
                sol::constructors<vili::parser::state(),
                    vili::parser::state(const vili::parser::state&)>());
        bindstate["set_indent"] = &vili::parser::state::set_indent;
        bindstate["use_indent"] = &vili::parser::state::use_indent;
        bindstate["set_active_identifier"] =

            [](vili::parser::state* self, std::string identifier) {
                self->set_active_identifier(std::move(identifier));
            }

        ;
        bindstate["set_active_template"] =

            [](vili::parser::state* self, std::string identifier) {
                self->set_active_template(std::move(identifier));
            }

        ;
        bindstate["open_block"] = &vili::parser::state::open_block;
        bindstate["close_block"] = &vili::parser::state::close_block;
        bindstate["push"] = &vili::parser::state_push_proxy;
        bindstate["push_template"] = sol::overload(
            static_cast<void (vili::parser::state::*)()>(&vili::parser::state::push_template),
            static_cast<void (vili::parser::state::*)(const std::string&, const vili::node&)>(
                &vili::parser::state::push_template));
        bindstate["specialize_template"] = &vili::parser::state::specialize_template;
        bindstate["get_template"] = &vili::parser::state::get_template;
        bindstate["root"] = &vili::parser::state::root;
    }
    void LoadClassError(sol::state_view state)
    {
        sol::table parserNamespace = state["vili"]["parser"].get<sol::table>();
        sol::usertype<vili::parser::error> binderror
            = parserNamespace.new_usertype<vili::parser::error>(
                "error", sol::call_constructor, sol::default_constructor);
    }
    void LoadFunctionStatePushProxy(sol::state_view state)
    {
        sol::table parserNamespace = state["vili"]["parser"].get<sol::table>();
        parserNamespace.set_function("state_push_proxy", vili::parser::state_push_proxy);
    }
    void LoadFunctionFromString(sol::state_view state)
    {
        sol::table parserNamespace = state["vili"]["parser"].get<sol::table>();
        parserNamespace.set_function("from_string",
            sol::overload(
                [](std::string_view data) -> vili::node { return vili::parser::from_string(data); },
                [](std::string_view data, vili::parser::state parser_state) -> vili::node {
                    return vili::parser::from_string(data, parser_state);
                }));
    }
    void LoadFunctionFromFile(sol::state_view state)
    {
        sol::table parserNamespace = state["vili"]["parser"].get<sol::table>();
        parserNamespace.set_function("from_file",
            sol::overload(
                [](std::string_view path) -> vili::node { return vili::parser::from_file(path); },
                [](std::string_view path, vili::parser::state parser_state) -> vili::node {
                    return vili::parser::from_file(path, parser_state);
                }));
    }
};