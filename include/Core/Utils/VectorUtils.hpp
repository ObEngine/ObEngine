#pragma once

#include <vili/ErrorHandler.hpp>

/**
 * \brief Functions to work with vectors (C++ Arrays)
 * @Bind
 */
namespace obe::Utils::Vector
{
    /**
     * \brief Check if a given item is in the given std::vector
     * \tparam V Type of the item you want to check
     * \param item Item you want to search in the std::vector
     * \param vec Reference of the std::vector you want to search the item in
     * \return true if the item is found in the std::vector, false otherwise
     */
    template <typename V> bool contains(V item, const std::vector<V>& vec);
    /**
     * \brief Get the index of an item in a std::vector
     * \tparam V Type of the item you want to check
     * \param item Item you want to search in the std::vector
     * \param vec Reference of the std::vector you want to search the item in
     * \return Index of the item in the std::vector
     */
    template <typename V> int indexOfElement(V item, const std::vector<V>& vec);
    /**
     * \brief Join all elements of a std::string into a std::string using a
     * separator \param vector Vector you want to join \param sep Separator you
     * want to use \param start From which index of the std::vector \param end
     * From which index (starting at the end) of the std::vector \return A
     * std::string which are all the elements of the std::vector joined
     */
    std::string join(std::vector<std::string>& vector, std::string sep = "",
        int start = 0, int end = 0);
    /**
     * \brief Erases all occurences of a given element in the std::vector
     * \tparam V Type of the item you want to erase
     * \param vec Reference of the std::vector you want to erase the item from
     * \param item Element you want to erase from the std::vector
     */
    template <typename V> void eraseAll(std::vector<V>& vec, V item);
    /**
     * \brief Get a subpart of the given std::vector
     * \tparam V Type of the content contained in the given std::vector
     * \param vec Vector you want to get the subpart
     * \param start From which index of the std::vector
     * \param end From which index (starting at the end) of the std::vector
     * \return The subvector from start index to end index of the initial
     * std::vector
     */
    template <typename V>
    std::vector<V> getSubVector(
        const std::vector<V>& vec, int start = 0, int end = 0);

    template <typename V> bool contains(V item, const std::vector<V>& vec)
    {
        for (size_t k = 0; k < vec.size(); k++)
        {
            if (item == vec[k])
                return true;
        }
        return false;
    }

    template <typename V> int indexOfElement(V item, const std::vector<V>& vec)
    {
        for (unsigned int k = 0; k < vec.size(); k++)
        {
            if (item == vec[k])
                return k;
        }
        throw aube::ErrorHandler::Raise(
            "ObEngine.FunctionsHeader.Vector.UnknownIndexOfElement");
    }

    template <typename V> void eraseAll(std::vector<V>& vec, V item)
    {
        std::vector<int> toErase;
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec.at(i) == item)
                toErase.push_back(i);
        }
        for (int i = toErase.size() - 1; i >= 0; i--)
            vec.erase(vec.begin() + toErase[i]);
    }

    template <typename V>
    std::vector<V> getSubVector(
        const std::vector<V>& vec, const int start, const int end)
    {
        auto first = vec.begin() + start;
        auto last = vec.end() - end;
        std::vector<V> newVec(first, last);
        return newVec;
    }
} // namespace obe::Utils::Vector