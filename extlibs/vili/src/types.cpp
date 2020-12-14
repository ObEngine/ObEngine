#include <vili/exceptions.hpp>
#include <vili/types.hpp>
#include <vili/utils.hpp>

namespace vili
{
    node_type value_type(std::string_view value)
    {
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
            return null_typename.data();
        if (type == node_type::integer)
            return integer_typename.data();
        if (type == node_type::number)
            return number_typename.data();
        if (type == node_type::string)
            return string_typename.data();
        if (type == node_type::boolean)
            return boolean_typename.data();
        if (type == node_type::array)
            return array_typename.data();
        if (type == node_type::object)
            return object_typename.data();
        return "";
    }

    std::ostream& operator<<(std::ostream& os, const node_type& m)
    {
        os << to_string(m);
        return os;
    }

    node_type from_string(std::string_view type)
    {
        if (type == null_typename)
        {
            return node_type::null;
        }
        else if (type == boolean_typename)
        {
            return node_type::boolean;
        }
        else if (type == integer_typename)
        {
            return node_type::integer;
        }
        else if (type == number_typename)
        {
            return node_type::number;
        }
        else if (type == string_typename)
        {
            return node_type::string;
        }
        else if (type == array_typename)
        {
            return node_type::array;
        }
        else if (type == object_typename)
        {
            return node_type::object;
        }
        else
        {
            throw exceptions::invalid_node_type(type, VILI_EXC_INFO);
        }
    }
}
