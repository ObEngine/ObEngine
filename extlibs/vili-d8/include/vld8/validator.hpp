#pragma once

#include <vili/node.hpp>

namespace vili::validator
{
    vili::node validate_integer(
        std::string location, const vili::node& validator, const vili::node& input);
    vili::node validate_number(
        std::string location, const vili::node& validator, const vili::node& input);
    vili::node validate_boolean(
        std::string location, const vili::node& validator, const vili::node& input);
    vili::node validate_string(
        std::string location, const vili::node& validator, const vili::node& input);
    vili::node validate_array(
        std::string location, const vili::node& validator, const vili::node& input);
    vili::node validate_object(
        std::string location, const vili::node& validator, const vili::node& input);
    vili::node validate_union(
        std::string location, const vili::node& validator, const vili::node& input);
    vili::node validate_node(
        std::string location, const vili::node& validator, const vili::node& input);
    vili::node validate_tree(const vili::node& validator, const vili::node& input);
}