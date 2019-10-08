#pragma once

#include <vili/ComplexNode.hpp>

namespace obe::Types
{
    /**
     * \brief A Base Class that represents a vili serializable object
     * @Bind
     */
    class Serializable
    {
    public:
        /**
         * \brief Dumps the content of the Serializable object to a ComplexNode
         * \param target ComplexNode where to serialize the object
         */
        virtual void dump(vili::ComplexNode& target) const = 0;
        /**
         * \brief Loads an object from a ComplexNode
         * \param data ComplexNode containing the data of the object
         */
        virtual void load(vili::ComplexNode& data) = 0;
    };
} // namespace obe::Types
