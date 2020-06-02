#include <vili/node.hpp>
#include <vili/parser/actions.hpp>
#include <vili/parser/grammar.hpp>
#include <vili/parser/grammar_errors.hpp>
#include <vili/parser/parser_state.hpp>
#include <vili/types.hpp>

#include <fstream>
#include <iostream>

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/trace.hpp>

namespace peg = tao::pegtl;

namespace vili::parser
{
    template <class input_type> vili::node parse(input_type&& input)
    {
        state parser_state;
        try
        {
            peg::parse<vili::parser::rules::grammar, vili::parser::action,
                vili::parser::control>(std::forward<input_type&&>(input), parser_state);
            // std::cout << "Begin parsing" << std::endl;
            /*peg::standard_trace<vili::parser::rules::grammar, vili::parser::action,
                vili::parser::control>(std::forward<input_type&&>(input), parser_state);*/
        }
        catch (peg::parse_error& e)
        {
            const auto p = e.positions.front();
            std::stringstream ss;
            ss << e.what() << '\n'
               << input.line_at(p) << '\n'
               << std::setw(p.byte_in_line) << ' ' << '^' << std::endl;
            throw exceptions::parsing_error(
                input.source(), p.line, p.byte_in_line, VILI_EXC_INFO)
                .nest(std::runtime_error(ss.str()));
        }
        /*catch (vili::exceptions::base_exception& e)
        {
            std::cerr << "vili::exception : " << e.what() << std::endl;
        }*/

        return parser_state.root;
    }

    vili::node from_string(std::string_view data)
    {
        peg::memory_input in(data.data(), "string_source");
        return parse(in);
    }

    vili::node from_file(std::string_view path)
    {
        peg::file_input in(path);
        return parse(in);
    }
}