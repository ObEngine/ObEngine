#include <Types/Identifiable.hpp>

namespace obe::types
{
    Identifiable::Identifiable(const std::string& id)
    {
        m_id = id;
    }

    void Identifiable::set_id(const std::string& id)
    {
        m_id = id;
    }

    std::string Identifiable::get_id() const
    {
        return m_id;
    }
} // namespace obe::types
