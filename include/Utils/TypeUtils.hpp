#pragma once

#include <Utils/StringUtils.hpp>
#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Utils
    {
        namespace Type
        {
            template <typename V>
            std::string getObjectType(V item);
            template <class T>
            std::string getClassType();

            template <typename V>
            std::string getObjectType(V item)
            {
                std::vector<std::string> splittedTypeName = String::split(typeid(item).name(), " ");
                return Vector::join(splittedTypeName, "", 1);
            }

            template <class T>
            std::string getClassType()
            {
                std::vector<std::string> splittedTypeName = String::split(typeid(T).name(), " ");
                return Vector::join(splittedTypeName, "", 1);
            }
        }
    }
}