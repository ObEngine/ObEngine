namespace obe
{
    namespace Utils
    {
        namespace Map
        {
            /**
             * \brief Check if the given value is found in the std::map
             * \tparam T Type of the std::map values
             * \tparam U Type of the std::map keys
             * \param item Value to search in the map
             * \param map Reference to the map you want to search the value in
             * \return true if the value has been found, false otherwise
             */
            template <typename T, typename U>
            bool valueInMap(T item, std::map<U, T>& map);
            /**
            * \brief Check if the given key is found in the std::map
            * \tparam T Type of the std::map values
            * \tparam U Type of the std::map keys
            * \param item key to search in the map
            * \param map Reference to the map you want to search the key in
            * \return true if the key has been found, false otherwise
            */
            template <typename T, typename U>
            bool keyInMap(T item, std::map<T, U>& map);

            template <typename T, typename U>
            bool valueInMap(T item, std::map<U, T>& map)
            {
                for (auto iterator = map.begin(); iterator != map.end(); ++iterator)
                {
                    if (iterator->second == item)
                        return true;
                }
                return false;
            }

            template <typename T, typename U>
            bool keyInMap(T item, std::map<T, U>& map)
            {
                for (auto iterator = map.begin(); iterator != map.end(); ++iterator)
                {
                    if (iterator->first == item)
                        return true;
                }
                return false;
            }
        }
    }
}