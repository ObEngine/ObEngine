#pragma once

#include <vili/node.hpp>

namespace vili::msgpack
{
    using MsgPackBuffer = std::vector<uint8_t>;

    vili::node from_string(const std::string& msgpack);
    std::string to_string(const vili::node& node);
    void dump_element(MsgPackBuffer& buffer, const vili::node& element);
}