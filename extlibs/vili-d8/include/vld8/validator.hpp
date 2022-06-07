#pragma once

#include <vili/node.hpp>

namespace vili::validator
{
    vili::node validate_integer(
        const std::string& location, const vili::node& validator, const vili::node& input);
    vili::node validate_number(
        const std::string& location, const vili::node& validator, const vili::node& input);
    vili::node validate_boolean(
        const std::string& location, const vili::node& validator, const vili::node& input);
    vili::node validate_string(
        const std::string& location, const vili::node& validator, const vili::node& input);
    vili::node validate_array(
        const std::string& location, const vili::node& validator, const vili::node& input);
    vili::node validate_object(
        const std::string& location, const vili::node& validator, const vili::node& input);
    vili::node validate_union(
        const std::string& location, const vili::node& validator, const vili::node& input);
    vili::node validate_node(
        const std::string& location, const vili::node& validator, const vili::node& input);
    vili::node validate_tree(const vili::node& validator, const vili::node& input);
}