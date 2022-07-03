#pragma once

#include <vili/node.hpp>
#include <vili/parser.hpp>
#include <vld8/validator.hpp>

namespace obe::types
{
    /**
     * \brief A Base Class that represents a vili serializable object
     * \todo rename validate_and_load to load with parameter validate=true
     *       current load method should be renamed and made protected
     */
    class Serializable
    {
    protected:
        /**
         * \brief Gets the validation schema of the Serializable object as a vili node
         * \return vili::node that contains the validation schema
         */
        [[nodiscard]] virtual vili::node schema() const = 0;
    public:
        virtual ~Serializable() = default;
        /**
         * \brief Dumps the content of the Serializable object to a vili node
         * \return vili::node that contains the object in a serialized format
         */
        [[nodiscard]] virtual vili::node dump() const = 0;
        /**
         * \brief Loads an object from a vili node
         * \param data vili node containing the data of the object
         */
        virtual void load(const vili::node& data) = 0;

        void load_from_file(const std::string& path);

        void validate_and_load(const vili::node& data);
    };

    inline void Serializable::load_from_file(const std::string& path)
    {
        const vili::node data = vili::parser::from_file(path);
        this->validate_and_load(data);
    }

    inline void Serializable::validate_and_load(const vili::node& data)
    {
        vili::validator::validate_tree(this->schema(), data);
        this->load(data);
    }
} // namespace obe::types
