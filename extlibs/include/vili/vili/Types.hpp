#pragma once

#include <string>

namespace vili
{
    /**
     * \brief An enum representing Types of existing Nodes
     */
    enum class NodeType
    {
        Node,
        ContainerNode,
        DataNode,
        ArrayNode,
        ComplexNode,
        LinkNode
    };

    /**
     * \brief An enum representing the DataType of the Data stored in DataNode (Or used in Parsing)
     */
    enum class DataType
    {
        /**
         * \brief A String value
         */
        String,
        /**
         * \brief An Integer value
         */
        Int,
        /**
         * \brief A Floating-point value
         */
        Float,
        /**
         * \brief A Boolean value (can be True or False)
         */
        Bool,
        /**
         * \brief A Range Generator
         */
        Range,
        /**
         * \brief A LinkNode definition
         */
        Link,
        /**
         * \brief A NodeTemplate definition
         */
        Template,
        /**
         * \brief Unknown DataType
         */
        Unknown
    };
    /**
     * \brief Prints a NodeType to a stream
     * \param os stream where to print the NodeType
     * \param m The NodeType to print
     * \return The given stream (to chain calls)
     */
    std::ostream& operator<<(std::ostream& os, const NodeType& m);
    /**
     * \brief Prints a DataType to a stream
     * \param os stream where to print the DataType
     * \param m The DataType to print
     * \return The given stream (to chain calls)
     */
    std::ostream& operator<<(std::ostream& os, const DataType& m);

    namespace Types
    {
        /**
         * \brief Converts a std::string to the appropriated DataType
         * \param type The DataType in std::string form
         * \return The converted DataType
         */
        DataType stringToDataType(const std::string& type);
        /**
         * \brief Determines the DataType of a string representation of the value
         * \param var String representation of the value
         * \return The DataType of the value
         */
        DataType getVarType(const std::string& var);
        /**
         * \brief Gets the default value for the given DataType
         * \param type The DataType you want to get the default value
         * \return The string representation of the default value for the given DataType
         */
        std::string getDefaultValueForType(DataType type);
        /**
         * \brief Converts a DataType to its name (in a std::string)
         * \param type DataType you want the name
         * \return A std::string containing the name of the given DataType
         */
        std::string dataTypeToString(DataType type);
        /**
        * \brief Converts a NodeType to its name (in a std::string)
        * \param type NodeType you want the name
        * \return A std::string containing the name of the given NodeType
        */
        std::string nodeTypeToString(NodeType type);
    }
}
