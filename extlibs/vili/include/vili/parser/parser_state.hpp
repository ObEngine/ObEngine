#pragma once

#include <stack>

#include <vili/node.hpp>

namespace vili::parser
{
    class node_in_stack
    {
    public:
        node* item;
        int indent;

        node_in_stack(node* node, int indent)
        {
            this->item = node;
            this->indent = indent;
        }
    };

    class state
    {
    private:
        std::string m_identifier;
        std::stack<node_in_stack> m_stack;
        int64_t m_indent_base = -1;
        int64_t m_indent_current = 0;
        vili::node* m_last_container = nullptr;

    public:
        node root;
        state();
        state(const state& state);
        state(state&& state);
        void set_indent(int64_t indent);
        void use_indent();
        void set_active_identifier(std::string&& identifier);
        void open_block();
        void close_block();
        void push(node&& data);
    };
}
