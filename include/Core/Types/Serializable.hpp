#pragma once

#include <vili/node.hpp>

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
         * \brief Dumps the content of the Serializable object to a vili node
         */
        virtual vili::node dump() const = 0;
        /**
         * \brief Loads an object from a vili node
         * \param data vili node containing the data of the object
         */
        virtual void load(const vili::node& data) = 0;
    };
} // namespace obe::Types
