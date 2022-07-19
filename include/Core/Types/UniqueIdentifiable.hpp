#pragma once

#include <string>

namespace obe::types
{
    /**
     * \brief A Base class that does carry an unique identifier
     */
    class UniqueIdentifiable
    {
    protected:
        std::string m_uuid;

    public:
        virtual ~UniqueIdentifiable() = default;

        /**
         * \brief Creates a new UniqueIdentifiable
         */
        UniqueIdentifiable();
        UniqueIdentifiable(const UniqueIdentifiable&) = delete;
        UniqueIdentifiable& operator=(const UniqueIdentifiable&) = delete;
        UniqueIdentifiable(UniqueIdentifiable&& other) noexcept;
        /**
         * \brief Get the unique id of the UniqueIdentifiable
         * \return A std::string containing the unique id of the UniqueIdentifiable
         */
        [[nodiscard]] std::string get_unique_id() const;
    };
} // namespace obe::types
