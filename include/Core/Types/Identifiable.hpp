#pragma once

#include <string>

namespace obe::Types
{
    /**
     * \brief A Base class that does carry an unique identifier for a given
     * category (Sprites / Colliders etc..)
     * @Bind
     */
    class Identifiable
    {
    protected:
        std::string m_id;

    public:
        virtual ~Identifiable() = default;
        /**
         * \brief Creates a new Identifiable
         * \param id A std::string containing the id of the Identifiable
         */
        explicit Identifiable(const std::string& id);
        /**
         * \brief Set a new id for the Identifiable
         * \param id Sets the id of the Identifiable
         */
        void setId(const std::string& id);
        /**
         * \brief Get the id of the Identifiable
         * \return A std::string containing the id of the Identifiable
         */
        std::string getId() const;
    };

    /**
     * \brief Exactly like Identifiable class except you can't change the Id
     * after creation
     */
    class ProtectedIdentifiable : protected Identifiable
    {
    protected:
        using Identifiable::Identifiable;

    public:
        using Identifiable::getId;
    };
} // namespace obe::Types