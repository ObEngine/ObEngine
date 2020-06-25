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
        std::variant<array::iterator, object::iterator> m_ptr;

    public:
        node_iterator(array::iterator value);
        node_iterator(object::iterator value);
        node_iterator(const node_iterator& other_it);
        node_iterator& operator++();
        bool operator!=(const node_iterator& rhs) const;
        node& operator*();
    };

    class const_node_iterator
    {
    private:
        std::variant<array::const_iterator, object::const_iterator> m_ptr;

    public:
        const_node_iterator(array::const_iterator value);
        const_node_iterator(object::const_iterator value);
        const_node_iterator(const const_node_iterator& other_it);
        const_node_iterator& operator++();
        bool operator!=(const const_node_iterator& rhs) const;
        const node& operator*();
    };

    using node_data
        = std::variant<std::monostate, object, array, integer, number, boolean, string>;
    /**
     * \helper{Lib/Internal/Vili.lua}
     * \brief Base Class for every Node in the Tree
     */
    class node
    {
    protected:
        node_data m_data;
        [[nodiscard]] std::string dump_array() const;
        [[nodiscard]] std::string dump_object(bool root) const;

    public:
        static node from_type(node_type type);
        /**
         * \brief Default constructor, node will have null type
         */
        node() = default;
        /**
         * \brief Same than vili::integer constructor
         */
        node(int value);
        /**
         * \brief Creates a node that contains an integer
         */
        node(integer value);
        /**
         * \brief Creates a node that contains a number
         */
        node(number value);
        /**
         * \brief Creates a node that contains a string
         */
        node(const string& value);
        /**
         * \brief Creates a node that contains a boolean
         */
        node(boolean value);
        /**
         * \brief Same than vili::string constructor
         */
        node(const char* value);
        /**
         * \brief Creates a node that contains an array (vector-like container)
         */
        node(const array& value);
        /**
         * \brief Creates a node that contains a object (map-like container)
         */
        node(const object& value);
        /**
         * \brief node copy constructor
         */
        node(const node& copy);
        /**
         * \brief node move constructor
         */
        node(node&& move) noexcept;
        /**
         * \brief node affectation operator
         */
        void operator=(const node& copy);

        /**
         * \brief Retrieves the type of the underlying value of the node
         * \return a node_type enum value which represent the type of the node
         */
        [[nodiscard]] node_type type() const;
        /**
         * \brief Dumps the node content as a string
         */
        [[nodiscard]] std::string dump(bool root = false) const;

        /**
         * \nobind
         * \brief Checks if the node contains a given type
         * \tparam type node_type enum value to test against the type of the underlying value of the node
         * \return true if the type is the same, false otherwise
         */
        template <node_type type>[[nodiscard]] bool is();
        /**
         * \nobind
         * \brief Checks if the node contains a given type
         * \tparam T type to test against the type of the underlying value of the node
         * \return true if the type is the same, false otherwise
         */
        template <class T>[[nodiscard]] bool is() const;
        /**
         * \brief Checks whether the underlying value is a primitive (boolean, integer, number, string) or not
         * \return true if the type of the node is a primitive, false otherwise
         */
        [[nodiscard]] bool is_primitive() const;
        /**
         * \brief Checks whether the underlying value is a container (array, object) or not
         * \return true if the type of the node is container, false otherwise
         */
        [[nodiscard]] bool is_container() const;
        /**
         * \brief Checks whether the node contains a value or node
         * \return true if the node contains a value, false otherwise
         */
        [[nodiscard]] bool is_null() const;
        /**
         * \brief Checks whether the underlying value is an integer
         * \return true if the node contains an integer, false otherwise
         */
        [[nodiscard]] bool is_integer() const;
        /**
         * \brief Checks whether the underlying value is a number
         * \return true if the node contains a number, false otherwise
         */
        [[nodiscard]] bool is_number() const;
        /**
         * \brief Checks whether the underlying value is an integer or a number
         * \return true if the node contains an integer or a number, false otherwise
         */
        [[nodiscard]] bool is_numeric() const;
        /**
         * \brief Checks whether the underlying value is a boolean
         * \return true if the node contains a boolean, false otherwise
         */
        [[nodiscard]] bool is_boolean() const;
        /**
         * \brief Checks whether the underlying value is a string
         * \return true if the node contains a string, false otherwise
         */
        [[nodiscard]] bool is_string() const;
        /**
         * \brief Checks whether the underlying value is an array
         * \return true if the node contains an array, false otherwise
         */
        [[nodiscard]] bool is_array() const;
        /**
         * \brief Checks whether the underlying value is an object
         * \return true if the node contains an object, false otherwise
         */
        [[nodiscard]] bool is_object() const;

        /**
         * \nobind
         * \brief Returns the node as the underlying type
         * \tparam T type you want to cast the node to
         * \throw invalid_cast exception when the type of the underlying value is not the same as T
         * \return underlying value of the node (of type T)
         */
        template <class T> T& as();
        /**
         * \nobind
         * \brief Returns the node as the underlying type
         * \tparam T type you want to cast the node to
         * \throw invalid_cast exception when the type of the underlying value is not the same as T
         * \return const reference to the value of the node (of type T)
         */
        template <class T> const T& as() const;

        /**
         * \brief Returns the node as a boolean
         * \throw invalid_cast exception when the type of the underlying value is not a boolean
         * \return node as a boolean
         */
        [[nodiscard]] boolean as_boolean() const;
        /**
         * \brief Returns the node as an integer
         * \throw invalid_cast exception when the type of the underlying value is not an integer
         * \return node as an integer
         */
        [[nodiscard]] integer as_integer() const;
        /**
         * \brief Returns the node as a number
         * \throw invalid_cast exception when the type of the underlying value is not a number
         * \return node as a number
         */
        [[nodiscard]] number as_number() const;
        /**
         * \brief Returns the node as a string
         * \throw invalid_cast exception when the type of the underlying value is not a string
         * \return node as a string
         */
        [[nodiscard]] string as_string() const;
        /**
         * \brief Returns the node as an array
         * \throw invalid_cast exception when the type of the underlying value is not an array
         * \return node as an array
         */
        [[nodiscard]] array as_array() const;
        /**
         * \brief Returns the node as an object
         * \throw invalid_cast exception when the type of the underlying value is not an object
         * \return node as an object
         */
        [[nodiscard]] object as_object() const;

        /**
         * \brief Access element at given key
         */
        node& operator[](const char* key);
        node& operator[](const std::string& key);
        node& operator[](size_t index);

        void push(const node& value);
        /**
         * \nobind
         */
        template <class value_type> void emplace(size_t index, value_type&& value);
        /**
         * \nobind
         */
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

        const_node_iterator begin() const;
        const_node_iterator end() const;

        object& items();
        const object& items() const;

        node& at(const std::string& key);
        node& at(size_t index);
        const node& at(const std::string& key) const;
        const node& at(size_t index) const;

        /**
         * \nobind
         * \brief Directly access underlying variant
         * \return reference to the underlying variant
         */
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
            map.emplace(key, std::forward<value_type>(value));
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
