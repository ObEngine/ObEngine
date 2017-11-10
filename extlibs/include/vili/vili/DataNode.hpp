#pragma once

#include <variant>

#include "../ErrorHandler.hpp"
#include "Node.hpp"

namespace vili
{
    /**
     * \brief A terminal Node that contains data (One of the types defined in vili::DataType)
     * @Bind
     */
    class DataNode : public Node
    {
    protected:
        std::variant<int, double, bool, std::string> m_data;
        /**
         * \brief The DataType of the DataNode
         */
        DataType m_dataType;
        /**
         * \brief Befriends function operator<< used to print a DataNode
         */
        friend std::ostream& operator<<(std::ostream& stream, const DataNode& node);
    public:
        /**
         * \brief Redefinition of ClassType to NodeType::DataNode
         */
        const static NodeType ClassType = NodeType::DataNode;
        /**
         * \brief Creates a new DataNode
         * \param parent Pointer to the parent ContainerNode
         * \param id Id of the new DataNode
         * \param dataType Type of data the DataNode is supposed to store
         */
        DataNode(ContainerNode* parent, const std::string& id, const DataType& dataType);
        /**
         * \brief Creates a new DataNode without parent ContainerNode
         * \param id Id of the new DataNode
         * \param dataType Type of data the DataNode is supposed to store
         */
        DataNode(const std::string& id, const DataType& dataType);

        DataNode(const DataNode& copy);

        ~DataNode() override;

        /**
         * \brief Gets a dumpable representation of the contained data
         * \return A std::string containing a dumpable representation of the contained data
         */
        std::string dumpData() const;
        /**
         * \brief Sets an Int value
         * \param var An int value
         */
        void set(int var);
        /**
        * \brief Sets a Float value
        * \param var A double value
        */
        void set(double var);
        /**
        * \brief Sets a String value
        * \param var A std::string value
        */
        void set(const std::string& var);
        /**
        * \brief Sets a String value
        * \param var A const char* value
        */
        void set(const char* var);
        /**
        * \brief Sets a Bool value
        * \param var A bool value
        */
        void set(bool var);
        /**
        * \brief Sets an Int value
        * \param var An int value
        */
        void operator=(int var);
        /**
        * \brief Sets a Float value
        * \param var A double value
        */
        void operator=(double var);
        /**
        * \brief Sets a String value
        * \param var A std::string value
        */
        void operator=(const std::string& var);
        /**
        * \brief Sets a String value
        * \param var A const char* value
        */
        void operator=(const char* var);
        /**
        * \brief Sets a Bool value
        * \param var A bool value
        */
        void operator=(bool var);
        /**
         * \brief Automatically determines the DataType and affects the value
         * \param rawData Value to set (String must be dumpable representation)
         */
        void autoset(const std::string& rawData);
        /**
         * \brief Gets the vili::DataType of the contained Data
         * \return An enum value from vili::DataType which is the DataType of the contained Data
         */
        DataType getDataType() const;

        /**
         * \brief Template method (overloaded by Template specialisation) to get the contained Data
         * \tparam T Type the Data should be casted to (int, bool, std::string, double)
         * \return The contained value casted to the desired type
         */
        template <class T>
        T get() const
        {
        }

        /**
        * \brief Copies the DataNode into a new ContainerNode
        * \param newParent Parent of the new copied DataNode
        * \param newid Id to set to the newly created DataNode
        */
        void copy(ContainerNode* newParent, const std::string& newid = "") const override;
        /**
         * \brief Writes the DataNode to a file
         * \param file File (std::ofstream) where to write the DataNode
         * \param spacing Default indentation of the file
         * \param depth Depth of the DataNode to write
         */
        void write(std::ofstream* file, const std::string& spacing, unsigned int depth) const override;
        /**
         * \brief Returns the Data contained in the DataNode casted to a std::string
         */
        operator std::string() const;
        /**
        * \brief Returns the Data contained in the DataNode casted to an unsigned int
        */
		operator unsigned int() const;
        /**
        * \brief Returns the Data contained in the DataNode casted to an int
        */
        operator int() const;
        /**
        * \brief Returns the Data contained in the DataNode casted to a double
        */
        operator double() const;
        /**
        * \brief Returns the Data contained in the DataNode casted to a bool
        */
        operator bool() const;
    };

    /**
     * \brief Prints a DataNode in a stream
     * \param stream Stream where to print the DataNode
     * \param node Node to print
     * \return The stream (to chain calls)
     */
    std::ostream& operator<<(std::ostream& stream, const DataNode& node);

    template <>
    inline int DataNode::get() const
    {
        if (m_dataType == DataType::Int)
            return std::get<int>(m_data);
        if (m_dataType == DataType::Float)
            return std::get<double>(m_data);
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.DataNode.WrongIntCast", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    template <>
    inline double DataNode::get() const
    {
        if (m_dataType == DataType::Float)
            return std::get<double>(m_data);
        if (m_dataType == DataType::Int)
            return std::get<int>(m_data);
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.DataNode.WrongFloatCast", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    template <>
    inline bool DataNode::get() const
    {
        if (m_dataType == DataType::Bool)
            return std::get<bool>(m_data);
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.DataNode.WrongBoolCast", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }

    template <>
    inline std::string DataNode::get() const
    {
        if (m_dataType == DataType::String)
            return std::get<std::string>(m_data);
        throw aube::ErrorHandler::Raise("Vili.ViliHeader.DataNode.WrongStringCast", {{"path", getNodePath()},{"type", Types::dataTypeToString(m_dataType)}});
    }
}
