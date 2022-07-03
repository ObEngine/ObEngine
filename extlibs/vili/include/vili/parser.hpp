#pragma once

#include <vili/node.hpp>
#include <vili/parser/parser_state.hpp>

namespace vili::parser
{
    vili::node from_string(std::string_view data, state parser_state = state {});
    vili::node from_file(std::string_view path);
}