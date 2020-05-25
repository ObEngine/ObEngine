#include <vili/types.hpp>
#include <vili/utils.hpp>

namespace vili
{
    node_type value_type(std::string_view value)
    {
        node_type attribute_type;
        if (value == true_value || value == false_value)
            return node_type::boolean;
        if (value.at(0) == '"' && value.at(value.size() - 1) == '"')
            return node_type::string;
        if (utils::string::is_float(value.data()))
            return node_type::number;
        if (utils::string::is_int(value.data()))
            return node_type::integer;
        return {};
    }

    std::string to_string(node_type type)
    {
        if (type == node_type::null)
            return "null";
        if (type == node_type::integer)
            return "integer";
        if (type == node_type::number)
            return "number";
        if (type == node_type::string)
            return "string";
        if (type == node_type::boolean)
            return "boolean";
        if (type == node_type::array)
            return "array";
        if (type == node_type::object)
            return "object";
        return "";
    }

    std::ostream& operator<<(std::ostream& os, const node_type& m)
    {
        os << to_string(m);
        return os;
    }
}
