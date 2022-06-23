#include <iostream>
#include <iterator>
#include <vili/node.hpp>
#include <vili/utils.hpp>

std::string indent(const std::string& text)
{
    return vili::utils::string::replace(text, "\n", "\n    ");
}

namespace vili
{
    node_iterator::node_iterator(array::iterator value)
        : m_ptr(value)
    {
    }

    node_iterator::node_iterator(object::iterator value)
        : m_ptr(value)
    {
    }

    node_iterator::node_iterator(const node_iterator& other_it)
        : m_ptr(other_it.m_ptr)
    {
    }

    node_iterator& node_iterator::operator++()
    {
        if (std::holds_alternative<array::iterator>(m_ptr))
        {
            ++std::get<array::iterator>(m_ptr);
        }
        else
        {
            ++std::get<object::iterator>(m_ptr);
        }

        return *this;
    }

    bool node_iterator::operator!=(const node_iterator& rhs) const
    {
        if (std::holds_alternative<array::iterator>(m_ptr))
        {
            return std::get<array::iterator>(m_ptr)
                != std::get<array::iterator>(rhs.m_ptr);
        }
        else
        {
            return std::get<object::iterator>(m_ptr)
                != std::get<object::iterator>(rhs.m_ptr);
        }
    }

    node& node_iterator::operator*()
    {
        if (std::holds_alternative<array::iterator>(m_ptr))
        {
            return *std::get<array::iterator>(m_ptr);
        }
        else
        {
            return std::get<object::iterator>(m_ptr)->second;
        }
    }

    const_node_iterator::const_node_iterator(array::const_iterator value)
        : m_ptr(value)
    {
    }

    const_node_iterator::const_node_iterator(object::const_iterator value)
        : m_ptr(value)
    {
    }

    const_node_iterator::const_node_iterator(const const_node_iterator& other_it)
        : m_ptr(other_it.m_ptr)
    {
    }

    const_node_iterator& const_node_iterator::operator++()
    {
        if (std::holds_alternative<array::const_iterator>(m_ptr))
        {
            ++std::get<array::const_iterator>(m_ptr);
        }
        else
        {
            ++std::get<object::const_iterator>(m_ptr);
        }

        return *this;
    }

    bool const_node_iterator::operator!=(const const_node_iterator& rhs) const
    {
        if (std::holds_alternative<array::const_iterator>(m_ptr))
        {
            return std::get<array::const_iterator>(m_ptr)
                != std::get<array::const_iterator>(rhs.m_ptr);
        }
        else
        {
            return std::get<object::const_iterator>(m_ptr)
                != std::get<object::const_iterator>(rhs.m_ptr);
        }
    }

    const node& const_node_iterator::operator*()
    {
        if (std::holds_alternative<array::const_iterator>(m_ptr))
        {
            return *std::get<array::const_iterator>(m_ptr);
        }
        else
        {
            return std::get<object::const_iterator>(m_ptr)->second;
        }
    }

    std::string node::dump_array() const
    {
        const auto& vector = std::get<array>(m_data);
        std::string dump_value = "[";
        for (auto it = vector.begin(); it != vector.end(); ++it)
        {
            dump_value += it->dump() + (it != (vector.end() - 1) ? ", " : "");
        }
        dump_value += "]";
        return dump_value;
    }

    std::string node::dump_object(bool root) const
    {
        const auto& map = std::get<object>(m_data);
        std::string dump_value = (root) ? "" : "{\n";
        size_t index = 0;
        const size_t max_size = this->size();
        for (const auto& [key, value] : map)
        {
            if (!value.is_null())
            {
                dump_value += "    " + key + ": " + indent(value.dump());
                if (index < max_size - 1)
                {
                    dump_value += ",\n";
                }
                else
                {
                    dump_value += "\n";
                }
            }
            index++;
        }
        if (!root)
            dump_value += "}";
        return dump_value;
    }

    node node::from_type(node_type type)
    {
        if (type == node_type::integer)
        {
            return vili::integer {};
        }
        else if (type == node_type::number)
        {
            return vili::number {};
        }
        else if (type == node_type::boolean)
        {
            return vili::boolean {};
        }
        else if (type == node_type::string)
        {
            return vili::string {};
        }
        else if (type == node_type::array)
        {
            return vili::array {};
        }
        else if (type == node_type::object)
        {
            return vili::object {};
        }
        else
        {
            throw exceptions::invalid_node_type(unknown_typename, VILI_EXC_INFO);
        }
    }

    node::node(int value)
    {
        m_data = static_cast<integer>(value);
    }

    node::node(integer value)
    {
        m_data = value;
    }

    node::node(number value)
    {
        m_data = value;
    }

    node::node(const string& value)
    {
        m_data = value;
    }

    node::node(std::string_view value)
    {
        m_data = std::string(value);
    }

    node::node(boolean value)
    {
        m_data = value;
    }

    node::node(const char* value)
    {
        m_data = std::string(value);
    }

    node::node(const array& value)
    {
        m_data = value;
    }

    node::node(const object& value)
    {
        m_data = value;
    }

    node::node(const node& copy)
    {
        m_data = copy.m_data;
    }

    node::node(node&& move) noexcept
    {
        m_data = std::move(move.m_data);
    }

    void node::operator=(const node& copy)
    {
        m_data = copy.m_data;
    }

    node_type node::type() const
    {
        if (is_null())
            return node_type::null;
        else if (std::holds_alternative<integer>(m_data))
            return node_type::integer;
        else if (std::holds_alternative<number>(m_data))
            return node_type::number;
        else if (std::holds_alternative<boolean>(m_data))
            return node_type::boolean;
        else if (std::holds_alternative<string>(m_data))
            return node_type::string;
        else if (std::holds_alternative<object>(m_data))
            return node_type::object;
        else if (std::holds_alternative<array>(m_data))
            return node_type::array;
        else
            throw exceptions::invalid_node_type(unknown_typename, VILI_EXC_INFO);
    }

    std::string node::dump(bool root) const
    {
        if (is_null())
            return "";
        else if (is<number>())
            return utils::string::truncate_float(std::to_string(as<number>()));
        else if (is<integer>())
            return std::to_string(as<integer>());
        else if (is<string>())
            return utils::string::quote(as<string>());
        else if (is<boolean>())
            return (as<boolean>() ? "true" : "false");
        else if (is<array>())
            return dump_array();
        else if (is<object>())
            return dump_object(root);
        else
            throw exceptions::invalid_node_type(unknown_typename, VILI_EXC_INFO);
    }

    bool node::is_primitive() const
    {
        if (is<integer>() || is<number>() || is<string>() || is<boolean>())
            return true;
        return false;
    }

    bool node::is_container() const
    {
        if (is<array>() || is<object>())
            return true;
        return false;
    }

    bool node::is_null() const
    {
        if (m_data.index())
            return false;
        return true;
    }

    bool node::is_integer() const
    {
        return is<integer>();
    }

    bool node::is_number() const
    {
        return is<number>();
    }

    bool node::is_numeric() const
    {
        return is<integer>() || is<number>();
    }

    bool node::is_boolean() const
    {
        return is<boolean>();
    }

    bool node::is_string() const
    {
        return is<string>();
    }

    bool node::is_array() const
    {
        return is<array>();
    }

    bool node::is_object() const
    {
        return is<object>();
    }

    boolean node::as_boolean() const
    {
        return as<boolean>();
    }

    integer node::as_integer() const
    {
        return as<integer>();
    }

    number node::as_number() const
    {
        return as<number>();
    }

    string node::as_string() const
    {
        return as<string>();
    }

    array node::as_array() const
    {
        return as<array>();
    }

    object node::as_object() const
    {
        return as<object>();
    }

    node& node::operator[](const char* key)
    {
        return operator[](std::string(key));
    }

    node& node::operator[](const std::string& key)
    {
        if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            return map[key];
        }
        throw exceptions::invalid_cast(object_typename, to_string(type()), VILI_EXC_INFO);
    }

    node& node::operator[](const size_t index)
    {
        return this->at(index);
    }

    node& node::operator[](unsigned int index)
    {
        return this->at(index);
    }

    const node & node::operator[](const char *key) const
    {
        return this->at(key);
    }

    const node & node::operator[](const std::string &key) const
    {
        return this->at(key);
    }

    const node & node::operator[](size_t index) const
    {
        return this->at(index);
    }

    size_t node::size() const
    {
        if (is<array>())
        {
            return std::get<array>(m_data).size();
        }
        if (is<object>())
        {
            return std::get<object>(m_data).size();
        }
        throw exceptions::invalid_cast(object_typename, to_string(type()), VILI_EXC_INFO);
    }

    bool node::empty() const
    {
        return this->size() == 0;
    }

    void node::clear()
    {
        if (is<array>())
        {
            std::get<array>(m_data).clear();
        }
        else if (is<object>())
        {
            std::get<object>(m_data).clear();
        }
        else
        {
            throw exceptions::invalid_cast(object_typename, to_string(type()),
                VILI_EXC_INFO); // TODO: Add array type
        }
    }

    node::operator std::string_view() const
    {
        return as<string>();
    }

    node::operator const std::basic_string<char> &() const
    {
        return as<string>();
    }

    node::operator integer() const
    {
        return as<integer>();
    }

    node::operator int() const
    {
        return static_cast<int>(as<integer>());
    }

    node::operator number() const
    {
        return as<number>();
    }

    node::operator boolean() const
    {
        return as<boolean>();
    }

    node::operator unsigned() const
    {
        return static_cast<unsigned>(as<integer>());
    }

    bool node::operator==(const vili::node& other) const
    {
        return m_data == other.m_data;
    }

    bool node::operator!=(const vili::node& other) const
    {
        return m_data != other.m_data;
    }

    std::ostream& operator<<(std::ostream& os, const node& elem)
    {
        os << elem.dump();
        return os;
    }

    void node::push(const node& value)
    {
        if (is<array>())
        {
            std::get<array>(m_data).push_back(value);
        }
        else
        {
            throw exceptions::invalid_cast(
                array_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    void node::insert(size_t index, const node& value)
    {
        if (is<array>())
        {
            auto& vector = std::get<array>(m_data);
            vector.insert(vector.cbegin() + index, value);
        }
        else
        {
            throw exceptions::invalid_cast(
                array_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    void node::insert(const std::string& key, node value)
    {
        if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            map.emplace(key, std::move(value));
        }
        else
        {
            throw exceptions::invalid_cast(
                object_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    void node::merge(node& value)
    {
        if (is<object>() && value.is<object>())
        {
            for (auto [key, val] : value.items())
            {
                if (this->contains(key))
                    this->at(key).merge(val);
                else
                    (*this)[key] = val;
            }
        }
        else if (is<array>() && value.is<array>())
        {
            for (node& node : value)
            {
                this->push(node);
            }
        }
        else
        {
            m_data = value.m_data;
        }
    }

    bool node::contains(const std::string& key) const
    {
        if (is<object>())
        {
            const vili::object& map = std::get<object>(m_data);
            if (map.find(key) != map.cend())
            {
                return true;
            }
            return false;
        }
        else
        {
            throw exceptions::invalid_cast(
                object_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    void node::erase(size_t index)
    {
        if (is<array>())
        {
            auto& vector = std::get<array>(m_data);
            if (index < vector.size())
            {
                vector.erase(vector.cbegin() + index);
            }
            else
            {
                throw exceptions::array_index_overflow(
                    index, vector.size(), VILI_EXC_INFO);
            }
        }
        else
        {
            throw exceptions::invalid_cast(
                array_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    void node::erase(size_t begin, size_t end)
    {
        if (is<array>())
        {
            auto& vector = std::get<array>(m_data);
            if (begin < vector.size() && end < vector.size())
            {
                vector.erase(vector.cbegin() + begin, vector.cbegin() + end);
            }
            else
            {
                throw exceptions::array_index_overflow(
                    begin, vector.size(), VILI_EXC_INFO); // TODO: Add end bound check
            }
        }
        else
        {
            throw exceptions::invalid_cast(
                array_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    void node::erase(const std::string& key)
    {
        if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            if (const auto& element = map.find(key); element != map.end())
            {
                map.erase(element);
            }
            else
            {
                throw exceptions::unknown_child_node(key, VILI_EXC_INFO);
            }
        }
        else
        {
            throw exceptions::invalid_cast(
                object_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    node& node::front()
    {
        if (is<array>())
        {
            return std::get<array>(m_data).front();
        }
        if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            return map.begin()->second;
        }
        throw exceptions::invalid_cast(
            object_typename, to_string(type()), VILI_EXC_INFO); // TODO: Add array
    }

    node& node::back()
    {
        if (is<array>())
        {
            return std::get<array>(m_data).back();
        }
        if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            auto& ref = map.rbegin()->second;
            return ref;
        }
        throw exceptions::invalid_cast(
            object_typename, to_string(type()), VILI_EXC_INFO); // TODO: Add array
    }

    node_iterator node::begin()
    {
        if (is<array>())
        {
            auto& vector = std::get<array>(m_data);
            return std::get<array>(m_data).begin();
        }
        else if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            return map.begin();
        }
        else
        {
            throw exceptions::invalid_cast(container_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    node_iterator node::end()
    {
        if (is<array>())
        {
            auto& vector = std::get<array>(m_data);
            return vector.end();
        }
        else if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            return map.end();
        }
        else
        {
            throw exceptions::invalid_cast(container_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    const_node_iterator node::begin() const
    {
        if (is<array>())
        {
            auto& vector = std::get<array>(m_data);
            return std::get<array>(m_data).begin();
        }
        else if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            return map.begin();
        }
        else
        {
            throw exceptions::invalid_cast(container_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    const_node_iterator node::end() const
    {
        if (is<array>())
        {
            auto& vector = std::get<array>(m_data);
            return vector.end();
        }
        else if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            return map.end();
        }
        else
        {
            throw exceptions::invalid_cast(container_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    object& node::items()
    {
        if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            return map;
        }
        else
        {
            throw exceptions::invalid_cast(object_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    const object& node::items() const
    {
        if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            return map;
        }
        else
        {
            throw exceptions::invalid_cast(object_typename, to_string(type()), VILI_EXC_INFO);
        }
    }

    node& node::at(const std::string& key)
    {
        if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            if (auto element = map.find(key); element != map.end())
            {
                return element->second;
            }
            else
            {
                throw exceptions::unknown_child_node(key, VILI_EXC_INFO);
            }
        }
        throw exceptions::invalid_cast(object_typename, to_string(type()), VILI_EXC_INFO);
    }

    node& node::at(size_t index)
    {
        if (is<array>())
        {
            auto& vector = std::get<array>(m_data);
            if (index < vector.size())
            {
                return vector.at(index);
            }
            throw exceptions::array_index_overflow(index, vector.size(), VILI_EXC_INFO);
        }
        throw exceptions::invalid_cast(array_typename, to_string(type()), VILI_EXC_INFO);
    }

    const node& node::at(const std::string& key) const
    {
        if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            if (const auto element = map.find(key); element != map.end())
            {
                return element->second;
            }
            else
            {
                throw exceptions::unknown_child_node(key, VILI_EXC_INFO);
            }
        }
        throw exceptions::invalid_cast(object_typename, to_string(type()), VILI_EXC_INFO);
    }

    const node& node::at(size_t index) const
    {
        if (is<array>())
        {
            auto& vector = std::get<array>(m_data);
            if (index < vector.size())
            {
                return vector.at(index);
            }
            throw exceptions::array_index_overflow(index, vector.size(), VILI_EXC_INFO);
        }
        throw exceptions::invalid_cast(array_typename, to_string(type()), VILI_EXC_INFO);
    }

    node_data& node::data()
    {
        return m_data;
    }
}
