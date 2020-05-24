#include <vili2/node.hpp>
#include <vili2/parser/actions.hpp>
#include <vili2/parser/grammar.hpp>
#include <vili2/parser/parser_state.hpp>
#include <vili2/types.hpp>

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
            peg::parse<vili::parser::rules::grammar, vili::parser::action>(
                input, parser_state);
            /*peg::standard_trace<vili::parser::rules::grammar, vili::parser::action>(
                std::forward<input_type&&>(input), parser_state);*/
        }
        catch (peg::parse_error& e)
        {
            const auto p = e.positions.front();
            std::cerr << e.what() << '\n'
                      << input.line_at(p) << '\n'
                      << std::setw(p.byte_in_line) << ' ' << '^' << std::endl;
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