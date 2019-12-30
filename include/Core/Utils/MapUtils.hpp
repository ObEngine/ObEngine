#pragma once

#include <map>
#include <vector>

/**
 * \brief Some functions to handle maps
 * @Bind
 */
namespace obe::Utils::Map
{
    /**
     * \brief Check if the given value is found in the std::map
     * \tparam T Type of the std::map values
     * \tparam U Type of the std::map keys
     * \param item Value to search in the map
     * \param map Reference to the map you want to search the value in
     * \return true if the value has been found, false otherwise
     */
    template <class MapType>
    bool valueInMap(typename MapType::value_type item, MapType&& map);
    /**
     * \brief Check if the given key is found in the std::map
     * \tparam T Type of the std::map values
     * \tparam U Type of the std::map keys
     * \param item key to search in the map
     * \param map Reference to the map you want to search the key in
     * \return true if the key has been found, false otherwise
     */
    template <class MapType>
    bool keyInMap(typename MapType::key_type item, MapType&& map);

    template <class MapType>
    std::vector<typename std::decay_t<MapType>::key_type> getKeys(
        MapType&& map);

    template <class MapType>
    bool valueInMap(typename MapType::value_type item, MapType&& map)
    {
        for (const auto& [key, value] : map)
        {
            if (value == item)
                return true;
        }
        return false;
    }

    template <class MapType>
    bool keyInMap(typename MapType::key_type item, MapType&& map)
    {
        for (const auto& [key, value] : map)
        {
            if (key == item)
                return true;
        }
        return false;
    }

    template <class MapType>
    std::vector<typename std::decay_t<MapType>::key_type> getKeys(MapType&& map)
    {
        std::vector<typename std::decay_t<MapType>::key_type> keys;
        keys.reserve(map.size());
        for (const auto& [key, value] : map)
            keys.push_back(key);
        return keys;
    }
} // namespace obe::Utils::Map