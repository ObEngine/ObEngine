#pragma once

#include <string>
#include <variant>

#include <vili/exceptions.hpp>
#include <vili/types.hpp>

namespace vili
{
    class node;

    class node_iterator
    {
    private:
        std::variant<array::value_type*, object::iterator> m_ptr;

    public:
        node_iterator(array::value_type* value);
        node_iterator(object::iterator value);
        node_iterator(const node_iterator& other_it);
        node_iterator& operator++();
        bool operator!=(const node_iterator& rhs) const;
        node& operator*();
    };

    using node_data
        = std::variant<std::monostate, object, array, integer, number, boolean, string>;
    /**
     * \brief Base Class for every Node in the Tree
     */
    class node
    {
    protected:
        node_data m_data;
        [[nodiscard]] std::string dump_array() const;
        [[nodiscard]] std::string dump_object(bool root) const;

    public:
        node() = default;
        node(int value);
        node(integer value);
        node(number value);
        node(const string& value);
        node(boolean value);
        node(const char* value);
        node(const array& value);
        node(const object& value);
        node(const node& copy);
        node(node&& move) noexcept;
        void operator=(const node& copy);

        [[nodiscard]] node_type type() const;
        [[nodiscard]] std::string dump(bool root = false) const;

        template <node_type type> bool is();
        template <class T>[[nodiscard]] bool is() const;
        [[nodiscard]] bool is_primitive() const;
        [[nodiscard]] bool is_container() const;
        [[nodiscard]] bool is_null() const;

        template <class T> T& as();
        template <class T> const T& as() const;

        node& operator[](const char* key);
        node& operator[](const std::string& key);
        node& operator[](size_t index);

        void push(const node& value);
        template <class value_type> void emplace(size_t index, value_type&& value);
        template <class value_type>
        void emplace(const std::string& key, value_type&& value);
        void insert(size_t index, const node& value);
        void insert(const std::string& key, node value);
        void merge(node& value);
        bool contains(const std::string& key) const;

        void erase(size_t index);
        void erase(size_t begin, size_t end);
        void erase(const std::string& key);

        node& front();
        node& back();

        node_iterator begin();
        node_iterator end();
        object& items();
        const object& items() const;

        node& at(const std::string& key);
        node& at(size_t index);
        const node& at(const std::string& key) const;
        const node& at(size_t index) const;

        node_data& data();

        [[nodiscard]] size_t size() const;
        [[nodiscard]] bool empty() const;

        void clear();

        operator std::string_view() const;
        operator const std::string&() const;
        operator integer() const;
        operator int() const;
        operator number() const;
        operator boolean() const;
        operator unsigned() const;
    };

    template <node_type type_enum> bool node::is()
    {
        return is<decltype(node_helper_t<type_enum>::type)>();
    }

    template <class T> bool node::is() const
    {
        return std::holds_alternative<T>(m_data);
    }

    template <class T> const T& node::as() const
    {
        if (is<T>())
            return std::get<T>(m_data);
        throw exceptions::invalid_cast(
            typeid(T).name(), to_string(type()), VILI_EXC_INFO);
    }

    template <class value_type> void node::emplace(size_t index, value_type&& value)
    {
        if (is<array>())
        {
            auto& vector = std::get<array>(m_data);
            vector.emplace(vector.cbegin() + index, std::forward(value));
        }
        else
        {
            throw exceptions::invalid_cast(array_type, to_string(type()), VILI_EXC_INFO);
        }
    }

    template <class value_type>
    void node::emplace(const std::string& key, value_type&& value)
    {
        if (is<object>())
        {
            auto& map = std::get<object>(m_data);
            map.emplace(key, std::forward(value));
        }
        else
        {
            throw exceptions::invalid_cast(object_type, to_string(type()), VILI_EXC_INFO);
        }
    }

    template <class T> T& node::as()
    {
        if (is<T>())
            return std::get<T>(m_data);
        throw exceptions::invalid_cast(
            typeid(T).name(), to_string(type()), VILI_EXC_INFO);
    }

    std::ostream& operator<<(std::ostream& os, const node& elem);
}
