#include <Types/Identifiable.hpp>

namespace obe
{
    namespace Types
    {
        Identifiable::Identifiable(const std::string& id)
        {
            m_id = id;
        }

        void Identifiable::setId(const std::string& id)
        {
            m_id = id;
        }

        std::string Identifiable::getId() const
        {
            return m_id;
        }
    }
}
