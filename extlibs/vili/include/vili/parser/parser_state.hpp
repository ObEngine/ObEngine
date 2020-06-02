#pragma once

#include <stack>
#include <unordered_map>

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
        std::string m_template_identifier;
        std::stack<node_in_stack> m_stack;
        int64_t m_indent_base = 4;
        int64_t m_indent_current = -1;
        std::unordered_map<std::string, node> m_templates;

    public:
        node root;
        state();
        void set_indent(int64_t indent);
        void use_indent();
        void set_active_identifier(std::string&& identifier);
        void set_active_template(std::string&& identifier);
        void open_block();
        void close_block();
        void push(node&& data);
        void push_template();
        [[nodiscard]] node get_template(const std::string& template_name) const;
    };
}
