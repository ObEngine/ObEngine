#include <vili/parser/parser_state.hpp>

namespace vili::parser
{
    state::state()
        : root(object {})
    {
        m_stack.emplace(&root, 0);
        m_templates["integer"] = vili::object {{"type", "integer"}};
        m_templates["number"] = vili::object {{"type", "number"}};
        m_templates["string"] = vili::object {{"type", "string"}};
        m_templates["boolean"] = vili::object {{"type", "boolean"}};
        m_templates["array"] = vili::object {{"type", "array"}};
        m_templates["object"] = vili::object {{"type", "object"}};
        m_templates["any"] = vili::object {{"type", "any"}};
        m_templates["union"] = vili::object {{"type", "union"}};
    }

    state::state(const state& state)
        : m_indent_base(state.m_indent_base)
        , m_templates(state.m_templates)
        , root(state.root)
    {
        m_stack.emplace(&root, 0);
    }

    state::state(state&& state)
        : m_indent_base(state.m_indent_base)
        , m_templates(std::move(state.m_templates))
        , root(state.root)
    {
        m_stack.emplace(&root, 0);
    }

    void state::set_indent(int64_t indent)
    {
        if (m_indent_base == -1 && indent > 0)
        {
            m_indent_base = indent;
        }
        if (indent % m_indent_base && m_stack.top().indent)
        {
            throw exceptions::inconsistent_indentation(
                indent, m_indent_base, VILI_EXC_INFO);
        }
        if (m_indent_base > 0)
        {
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
                if (indent - m_indent_current > 1 || indent > m_stack.top().indent)
                {
                    throw exceptions::too_much_indentation(indent, VILI_EXC_INFO);
                }
            }
            m_indent_current = indent;
        }
    }

    void state::use_indent()
    {
        m_stack.top().indent = static_cast<int>(m_indent_current) + 1;
    }

    void state::set_active_identifier(std::string&& identifier)
    {
        m_identifier = identifier;
    }

    void state::set_active_template(std::string&& identifier)
    {
        m_template_identifier = identifier;
        m_identifier = identifier;
    }

    void state::open_block()
    {
        m_stack.emplace(m_last_container, 0);
    }

    void state::close_block()
    {
        m_stack.pop();
    }

    void state::push(node&& data)
    {
        node& top = *m_stack.top().item;
        if (top.is<array>())
        {
            top.push(data);
            if (data.is_container())
            {
                m_last_container = &top.back();
            }
        }
        else if (top.is<object>())
        {
            if (m_identifier.empty())
            {
                // Template specialization
                top.back().merge(data);
            }
            else
            {
                if (top.contains(m_identifier))
                {
                    // Object redefinition
                    top.at(m_identifier).merge(data);
                }
                else
                {
                    top.insert(m_identifier, data);
                }
                if (data.is_container())
                {
                    m_last_container = &top.at(m_identifier);
                }
            }
            m_identifier.clear();
        }
        else
        {
            throw std::runtime_error("Should not happen");
        }
    }

    void state::push_template()
    {
        node& top = *m_stack.top().item;
        if (top.empty())
            m_templates[m_template_identifier] = top;
        else
        {
            m_templates[m_template_identifier] = top.back();
            top.erase(m_template_identifier);
        }
        m_template_identifier.clear();
    }

    void state::push_template(
        const std::string& template_name, const vili::node& node_template)
    {
        m_templates.emplace(template_name, node_template);
    }

    void state::specialize_template()
    {
        node& top = *m_stack.top().item;
        if (top.is<vili::array>())
        {
            top[top.size() - 2].merge(top[top.size() - 1]);
            top.erase(top.size() - 1);
        }
    }

    node state::get_template(const std::string& template_name) const
    {
        if (const auto it = m_templates.find(template_name); it != m_templates.end())
        {
            return it->second;
        }
        std::vector<std::string> templates_names;
        templates_names.reserve(m_templates.size());
        std::transform(m_templates.begin(), m_templates.end(), std::back_inserter(templates_names),
            [](const auto& template_pair) {
                return template_pair.first;
            });
        throw exceptions::unknown_template(template_name, templates_names, VILI_EXC_INFO);
    }
}