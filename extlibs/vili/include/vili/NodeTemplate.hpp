#pragma once

#include <LinkNode.hpp>

namespace vili
{
    /**
     * \brief Constraints a NodeTemplate parameter
     */
    class NodeConstraintManager
    {
    private:
        LinkNode m_attribute;
        std::vector<std::function<bool(DataNode*)>> m_constraints;
    public:
        /**
         * \brief Creates a new NodeConstraintManager
         * \param parent Parent of the contained LinkNode
         * \param path Path that the LinkNode should point to
         */
        NodeConstraintManager(ComplexNode* parent, const std::string& path);
        /**
         * \brief Adds a new constraint to the NodeConstraintManager
         * \param constraint A function with one DataNode parameter that should return true if the constraint is respected, false otherwise
         */
        void addConstraint(std::function<bool(DataNode*)> constraint);
        /**
         * \brief Checks if all constraints on the Argument value are accepted
         * \return true if the value for the argument respects all the constraints, false otherwise 
         */
        bool checkAllConstraints();
        /**
         * \brief Get the LinkNode linked to the argument
         * \return A pointer to the LinkNode
         */
        LinkNode* getLinkNode();
        /**
         * \brief Get the path (in the tree of NodeTemplate body) of the Argument
         * \return A std::string containing the path to the Argument
         */
        std::string getArgumentPath() const;
    };

    /**
     * \brief Transforms a Node Constructor to a ComplexNode
     */
    class NodeTemplate
    {
    private:
        std::string m_name;
        std::vector<NodeConstraintManager> m_signature;
        ComplexNode m_body;
        bool m_visible = true;
        bool m_signatureEnd = false;
        bool m_defaultLinkRoot = false;
        bool checkSignature();
    public:
        /**
         * \brief Creates a new NodeTemplate
         * \param name Name of the NodeTemplate
         */
        NodeTemplate(const std::string& name);
        /**
         * \brief Gets the generated ComplexNode structure of the NodeTemplate
         * \return A pointed to the generated ComplexNode structure of the NodeTemplate
         */
        ComplexNode* getBody();
        /**
         * \brief Builds the NodeTemplate and creates the ComplexNode in parent
         * \param parent ComplexNode where to place the newly built ComplexNode
         * \param id Id to give to the newly built ComplexNode
         */
        void build(ComplexNode* parent, const std::string& id);
        /**
         * \brief Adds a NodeConstraintManager to the NodeTemplate
         * \param constraintManager NodeConstraintManager to add to the NodeTemplate
         * \param facultative Should be equal to true if the Constraint is facultative, false if it is required
         */
        void addConstraintManager(const NodeConstraintManager& constraintManager, bool facultative = false);
        /**
         * \brief Enables usage of default __linkroot__
         */
        void useDefaultLinkRoot();
        /**
         * \brief Gets the amount of arguments of the NodeTemplate
         * \return An unsigned int containing the amount of arguments of the NodeTemplate
         */
        unsigned int getArgumentCount() const;
        /**
         * \brief Gets the name of the NodeTemplate
         * \return A std::string containing the name of the NodeTemplate
         */
        std::string getName() const;
        /**
         * \brief Sets the visibility of the NodeTemplate (non-visible NodeTemplate won't be dumped to a file)
         * \param visible Should be equal to true if the NodeTemplate should be visible, false otherwise
         */
        void setVisible(bool visible);
        /**
         * \brief Gets the visibility of the NodeTemplate
         * \return true if the NodeTemplate is visible, false otherwise
         */
        bool isVisible() const;
    };
}
