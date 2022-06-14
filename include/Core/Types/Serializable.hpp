#pragma once

#include <vili/node.hpp>
#include <vld8/validator.hpp>

namespace obe::Types
{
    /**
     * \brief A Base Class that represents a vili serializable object
     */
    class Serializable
    {
    public:
        virtual ~Serializable() = default;

        /**
         * \brief Gets the validation schema of the Serializable object as a vili node
         * \return vili::node that contains the validation schema
         */
        [[nodiscard]] virtual vili::node schema() const = 0;
        /**
         * \brief Dumps the content of the Serializable object to a vili node
         * \return vili::node that contains the object in a serialized format
         */
        virtual vili::node dump() const = 0;
        /**
         * \brief Loads an object from a vili node
         * \param data vili node containing the data of the object
         */
        virtual void load(const vili::node& data) = 0;

        void validate_and_load(const vili::node& data);
    };

    inline void Serializable::validate_and_load(const vili::node& data)
    {
        vili::validator::validate_tree(this->schema(), data);
        this->load(data);
    }
} // namespace obe::Types
