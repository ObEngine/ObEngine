#include <vili/node.hpp>

namespace vili::parser
{
    vili::node from_string(std::string_view data);
    vili::node from_file(std::string_view path);
}