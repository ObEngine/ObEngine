#pragma once

#include <vector>
#include <memory>

#include "DataNode.hpp"
#include "ContainerNode.hpp"

namespace vili
{
    /**
     * \brief An ArrayNode is a Node that can contains multiple DataNodes with an index
     * @Bind
     */
    class ArrayNode : public ContainerNode
    {
    private:
        std::vector<std::unique_ptr<DataNode>> m_dataList;
        std::vector<DataNode*> m_iteratorCache;
        void reorder(int index);
    public:
        /**
         * \brief Redefines the ClassType to ArrayNode
         */
        const static NodeType ClassType = NodeType::ArrayNode;
        /**
         * \brief Creates a new ArrayNode
         * \param parent Parent of the ArrayNode
         * \param id Id of the ArrayNode
         */
        ArrayNode(ContainerNode* parent, const std::string& id);
        /**
         * \brief Creates an orphan new ArrayNode
         * \param id Id of the ArrayNode
         */
        ArrayNode(const std::string& id);

        ArrayNode(const ArrayNode& copy);

        ~ArrayNode() override;

        /**
         * \brief Gets the size of the ArrayNode (Amount of contained Nodes)
         * \return An unsigned int containing the size of the ArrayNode
         */
        unsigned int size() const;
        /**
         * \brief Access a contained DataNode
         * \param index Index of the contained DataNode
         * \return A reference to the contained DataNode at the given index
         */
        DataNode& get(unsigned int index) const;
        /**
        * \brief Access a contained DataNode
        * \param index Index of the contained DataNode
        * \return A reference to the contained DataNode at the given index
        */
        DataNode& operator[](unsigned int index) const;
        /**
         * \brief Used for range based iteration
         * \return A std::vector<DataNode*>::iterator pointing to the first DataNode (in a cache)
         */
        std::vector<DataNode*>::iterator begin();
        /**
         * \brief Used for range based iteration
         * \return A std::vector<DataNode*>::iterator pointing to the last DataNode (in a cache)
         */
        std::vector<DataNode*>::iterator end();
        /**
         * \brief Pushes a new String-typed DataNode in the ArrayNode
         * \param element Value of the new DataNode to push in the ArrayNode
         */
        void push(const std::string& element);
        /**
        * \brief Pushes a new Int-typed DataNode in the ArrayNode
        * \param element Value of the new DataNode to push in the ArrayNode
        */
        void push(int element);
        /**
        * \brief Pushes a new Bool-typed DataNode in the ArrayNode
        * \param element Value of the new DataNode to push in the ArrayNode
        */
        void push(bool element);
        /**
        * \brief Pushes a new Float-typed DataNode in the ArrayNode
        * \param element Value of the new DataNode to push in the ArrayNode
        */
        void push(double element);
        /**
         * \brief Inserts a new String-Typed DataNode at the given index in the ArrayNode
         * \param index Index where to insert the DataNode
         * \param element Value of the new DataNode to insert in the ArrayNode
         */
        void insert(unsigned int index, const std::string& element);
        /**
        * \brief Inserts a new Int-Type DataNode at the given index in the ArrayNode
        * \param index Index where to insert the DataNode
        * \param element Value of the new DataNode to insert in the ArrayNode
        */
        void insert(unsigned int index, int element);
        /**
        * \brief Inserts a new Bool-Typed DataNode at the given index in the ArrayNode
        * \param index Index where to insert the DataNode
        * \param element Value of the new DataNode to insert in the ArrayNode
        */
        void insert(unsigned int index, bool element);
        /**
        * \brief Inserts a new Float-Typed DataNode at the given index in the ArrayNode
        * \param index Index where to insert the DataNode
        * \param element Value of the new DataNode to insert in the ArrayNode
        */
        void insert(unsigned int index, double element);
        /**
         * \brief Clears all DataNodes contained in the ArrayNode
         */
        void clear();
        /**
         * \brief Erases a DataNode from the ArrayNode
         * \param index Index of the DataNode to erase (RIP little DataNode)
         */
        void erase(unsigned int index);
        /**
        * \brief Removes ownership and child Node from ContainerNode (Node won't be memory managed anymore, be cautious)
        * \param element Element to free from its parent
        * \return Pointer to the child Node
        */
        Node* extractElement(Node* element) override;
        /**
        * \brief Copies the ArrayNode into a new ContainerNode
        * \param newParent Parent of the new copied Node
        * \param newid Id to set to the newly created Node
        */
        void copy(ContainerNode* newParent, const std::string& newid = "") const override;
        /**
        * \brief Writes the ArrayNode to a file
        * \param file File (std::ofstream) where to write the Node
        * \param spacing Default indentation of the file
        * \param depth Depth of the Node to write
        */
        void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const override;
    };
}
