#pragma once

#include <vili/parser/grammar.hpp>
#include <vili/parser/parser_state.hpp>

namespace vili::parser
{
    template <typename Rule> struct action
    {
    };

    template <> struct action<rules::string_content>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.push(in.string());
        }
    };

    template <> struct action<rules::number>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            const std::string_view data_in = in.string_view();
            state.push(utils::string::to_double(in.string_view()));
        }
    };

    template <> struct action<rules::integer>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.push(utils::string::to_long(in.string_view()));
        }
    };

    template <> struct action<rules::boolean>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.push((in.string_view() == "true" ? true : false));
        }
    };

    template <> struct action<rules::template_identifier_usage>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            try
            {
                state.push(state.get_template(in.string()));
            }
            catch (exceptions::unknown_template& e)
            {
                throw exceptions::parsing_error(in.position().source, in.position().line,
                    in.position().byte, VILI_EXC_INFO)
                    .nest(e);
            }
        }
    };

    template <> struct action<rules::identifier>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.set_active_identifier(std::move(in.string()));
        }
    };

    template <> struct action<rules::open_array>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.push(vili::array {});
            state.open_block();
        }
    };

    template <> struct action<rules::close_array>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.close_block();
        }
    };

    template <> struct action<rules::open_object>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.push(vili::object {});
            state.open_block();
        }
    };

    template <> struct action<rules::close_object>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.close_block();
        }
    };

    template <> struct action<rules::indent_based_object>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.push(vili::object {});
            state.open_block();
            state.use_indent();
        }
    };

    template <> struct action<rules::indent>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            try
            {
                state.set_indent(in.string_view().size());
            }
            catch (vili::exceptions::base_exception& e)
            {
                throw exceptions::parsing_error(in.position().source, in.position().line,
                    in.position().byte, VILI_EXC_INFO)
                    .nest(e);
            }
        }
    };

    template <> struct action<rules::template_keyword>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.set_indent(0);
        }
    };

    template <> struct action<rules::template_identifier>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.set_active_template(std::move(in.string()));
        }
    };

    template <> struct action<rules::template_decl>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.push_template();
        }
    };

    template <> struct action<rules::template_specialization>
    {
        template <class ParseInput> static void apply(const ParseInput& in, state& state)
        {
            state.specialize_template();
        }
    };
}