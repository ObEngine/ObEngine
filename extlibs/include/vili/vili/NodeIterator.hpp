#pragma once

#include <vector>

namespace vili
{
    class ComplexNode;

    /**
     * \brief A class that can be used in argument in the ComplexNode::walk function to walk through the whole tree
     */
    class NodeIterator
    {
    protected:
        std::vector<ComplexNode*> m_cache;
        bool m_over = false;
        unsigned int m_index = 0;
        ComplexNode* m_node = nullptr;
        void next();
        void next(ComplexNode* node);
        friend class ComplexNode;
    public:
        /**
         * \brief Creates a new NodeIterator in realtime mode
         */
        NodeIterator();
        /**
         * \brief Creates a new NodeIterator in cached mode
         * \param node ComplexNode used to generate the cache (The ComplexNode that will be used to walk)
         */
        NodeIterator(ComplexNode* node);
        /**
         * \brief Access the current ComplexNode through the arrow operator
         * \return A pointer to the current ComplexNode
         */
        ComplexNode* operator->() const;
        /**
         * \brief Access the current ComplexNode
         * \return A pointer to the current ComplexNode
         */
        ComplexNode* get() const;
        /**
         * \brief Gets if the NodeIterator uses a cache or not
         * \return true if the NodeIterator is in cache mode, false if it is in realtime mode
         */
        bool hasCache() const;
        /**
         * \brief Current step of the walk (only in cached mode)
         * \return An unsigned int containing the current step of the walk
         */
        unsigned int index() const;
        /**
         * \brief The total amount of steps of the walk (only in cached mode)
         * \return An unsigned int containing the total amount of steps of the walk
         */
        unsigned int size() const;
        /**
         * \brief Gets if the current Node is the first one (only in cached mode)
         * \return true if the current Node is the first one, false otherwise
         */
        bool first() const;
        /**
        * \brief Gets if the current Node is the last one (only in cached mode)
        * \return true if the current Node is the last one, false otherwise
        */
        bool last() const;
        /**
         * \brief Gets if the walk is over
         * \return true if the walk is over, false otherwise
         */
        bool over() const;
        /**
         * \brief Stops the walk
         */
        void terminate();
    };
}
