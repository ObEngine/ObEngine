#include <Input/InputSource.hpp>

namespace obe::input
{
    InputSource::InputSource(const std::string& input_type, const std::string& name, const std::string& printable_char)
        : m_input_type(input_type)
        , m_name(name)
        , m_printable_char(printable_char)
    {
    }

    std::string InputSource::get_input_type() const
    {
        return m_input_type;
    }

    std::string InputSource::get_printable_char() const
    {
        return m_printable_char;
    }

    bool InputSource::is_printable() const
    {
        return !m_printable_char.empty();
    }

    std::string InputSource::get_name() const
    {
        return m_name;
    }
}
