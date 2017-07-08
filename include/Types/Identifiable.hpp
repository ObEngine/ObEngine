#pragma once

#include <string>

namespace obe
{
    namespace Types
    {
        class Identifiable
        {
            protected:
                std::string m_id;
            public:
                explicit Identifiable(const std::string& id);
                void setId(const std::string& id);
                std::string getId() const;
        };
    }
}