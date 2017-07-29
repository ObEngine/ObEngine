#pragma once

#include "NodeIterator.hpp"

namespace vili
{
    /**
     * \brief Almost like the NodeIterator except it should return a result
     * \tparam T Type the NodeValidator should return (validate)
     * @Bind
     */
    template <class T>
    class NodeValidator : public NodeIterator
    {
    private:
        T m_result;
    public:
        /**
         * \brief Creates a new NodeValidator in realtime mode
         */
        NodeValidator();
        /**
        * \brief Creates a new NodeValidator in cached mode
        * \param node ComplexNode used to generate the cache (The ComplexNode that will be used to walk)
        */
        NodeValidator(ComplexNode* node);
        /**
         * \brief Stops the iteration and returns the given result
         * \param result Value to return
         */
        void validate(T result);
        /**
         * \brief Gets the result returned using the NodeValidator::validate method
         * \return The returned value
         */
        T result();
    };
}
