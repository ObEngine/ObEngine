#include <vili2/parser/parser_state.hpp>

namespace vili::parser
{
    state::state()
        : root(object {})
    {
        m_stack.emplace(&root, 0);
    }

    void state::set_indent(int64_t indent)
    {
        if (m_indent_current == -1 && indent > 0)
        {
            m_indent_base = indent;
        }
        if (indent % m_indent_base && m_stack.top().indent)
        {
            throw exceptions::inconsistent_indentation(indent, m_indent_base, VILI_EXC_INFO);
        }
        indent /= m_indent_base; // Normalize indentation to "levels"
        if (m_indent_current > indent)
        {
            for (auto decrease_indent = m_indent_current; decrease_indent > indent;
                 decrease_indent--)
            {
                this->close_block();
            }
        }
        else if (m_indent_current == indent && indent < m_stack.top().indent)
        {
            this->close_block();
        }
        else if (m_indent_current < indent)
        {
            if (m_indent_current - indent > 1)
            {
                throw exceptions::too_much_indentation(indent, VILI_EXC_INFO);
            }
        }
        m_indent_current = indent;
    }

    void state::use_indent()
    {
        m_stack.top().indent = m_indent_current + 1;
    }

    void state::set_active_identifier(const std::string& identifier)
    {
        m_identifier = identifier;
    }

    void state::open_block()
    {
        m_stack.top().item->insert(m_identifier, node {});
        m_stack.emplace(&m_stack.top().item->at(m_identifier), 0);
    }

    void state::close_block()
    {
        m_stack.pop();
    }

    void state::push(node&& data)
    {
        node& top = *m_stack.top().item;
        const bool is_container = data.is_container();
        if (top.is<array>())
        {
            top.push(data);
        }
        else if (top.is<object>())
        {
            top.insert(m_identifier, std::move(data));
        }
        else
        {
            throw std::runtime_error("Should not happen");
        }
        if (is_container)
        {
            m_stack.emplace(&top.back(), 0);
        }
    }

    void state::push_template()
    {
        node& top = *m_stack.top().item;
        if (top.empty())
            m_templates[m_identifier] = top;
        else
            m_templates[m_identifier] = top.back();
    }

    node state::get_template(const std::string& template_name) const
    {
        if (const auto it = m_templates.find(template_name); it != m_templates.end())
        {
            return it->second;
        }
        throw exceptions::unknown_template(template_name, VILI_EXC_INFO);
    }
}