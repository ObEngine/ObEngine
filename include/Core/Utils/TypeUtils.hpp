#pragma once

#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>

/**
 * \brief Functions to work with Types
 * @Bind
 */
namespace obe::Utils::Type
{
    /**
     * \brief Return the type of an object in std::string form
     * \tparam V Type of the object you want to check
     * \param item Object to get the type from
     * \return The type of the object in std::string form
     */
    template <typename V> std::string getObjectType(V item);
    /**
     * \brief Return the type of an class in std::string form
     * \tparam T Type of the class you want to check
     * \return The type of the class in std::string form
     */
    template <class T> std::string getClassType();

    template <typename V> std::string getObjectType(V item)
    {
        std::vector<std::string> splittedTypeName
            = String::split(typeid(item).name(), " ");
        return Vector::join(splittedTypeName, "", 1);
    }

    template <class T> std::string getClassType()
    {
        std::vector<std::string> splittedTypeName
            = String::split(typeid(T).name(), " ");
        return Vector::join(splittedTypeName, "", 1);
    }
} // namespace obe::Utils::Type