#pragma once

#include <string>
#include <vector>

/**
 * \brief Functions to work with vectors (C++ Arrays)
 */
namespace obe::utils::vector
{
    /**
     * \brief Check if a given item is in the given std::vector
     * \tparam V Type of the item you want to check
     * \param item Item you want to search in the std::vector
     * \param vec Reference of the std::vector you want to search the item in
     * \return true if the item is found in the std::vector, false otherwise
     * \thints
     * \thint{contains, V=$primitives}
     * \endthints
     */
    template <typename V>
    bool contains(V item, const std::vector<V>& vec);
    /**
     * \brief Join all elements of a std::string into a std::string using a
     *        separator
     * \param vector array containing the strings to join
     * \param sep string separator used to join the string values from the array
     * \param start start position from where to start joining values
     * \param end from which index (starting at the end) of the array to stop joining values
     * \return A string which are all the elements of the std::vector joined
     *
     * \paramrename{end,stop}
     */
    std::string join(
        std::vector<std::string>& vector, std::string sep = "", int start = 0, int end = 0);

    template <typename V>
    bool contains(V item, const std::vector<V>& vec)
    {
        for (size_t k = 0; k < vec.size(); k++)
        {
            if (item == vec[k])
                return true;
        }
        return false;
    }
} // namespace obe::utils::vector
