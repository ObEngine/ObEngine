namespace obe
{
    namespace Utils
    {
        namespace Map
        {
            template <typename T, typename U>
            bool isInMap(T item, std::map<U, T>& map);
            template <typename T, typename U>
            bool keyInMap(T item, std::map<T, U>& map);

            template <typename T, typename U>
            bool isInMap(T item, std::map<U, T>& map)
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