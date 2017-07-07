#pragma once

#include <vili/ErrorHandler.hpp>

namespace obe
{
    namespace Utils
    {
        namespace Vector
        {
            template <typename V>
            bool isInList(V item, const std::vector<V>& vector);
            template <typename V>
            int indexOfElement(V item, const std::vector<V>& vector);
            std::string join(std::vector<std::string>& vector, std::string sep = "", int start = 0, int end = 0);
            template <typename V>
            void eraseAll(std::vector<V>& vector, V elem);
            void joinBetween(std::vector<std::string>& vector, std::string joinValue, std::string sep = "");
            void mergeNeighboors(std::vector<std::string>& vector, std::string n1, std::string n2, std::string sep = "", bool strict = false);
            template <typename V>
            int findSubVector(std::vector<V>& vector, std::vector<V>& find);
            template <typename V>
            std::vector<V> getSubVector(const std::vector<V>& vector, int start = 0, int end = 0);

            template <typename V>
            bool isInList(V term, const std::vector<V>& list1)
            {
                for (size_t k = 0; k < list1.size(); k++)
                {
                    if (term == list1[k])
                        return true;
                }
                return false;
            }

            template <typename V>
            int indexOfElement(V item, const std::vector<V>& vector)
            {
                for (unsigned int k = 0; k < vector.size(); k++)
                {
                    if (item == vector[k])
                        return k;
                }
                throw aube::ErrorHandler::Raise("ObEngine.FunctionsHeader.Vector.UnknownIndexOfElement", {{"element", std::to_string(item)}});
            }

            template <typename V>
            void eraseAll(std::vector<V>& vector, V elem)
            {
                std::vector<int> toErase;
                for (int i = 0; i < vector.size(); i++)
                {
                    if (vector.at(i) == elem)
                        toErase.push_back(i);
                }
                for (int i = toErase.size() - 1; i >= 0; i--)
                    vector.erase(vector.begin() + toErase[i]);
            }

            template <typename V>
            int findSubVector(std::vector<V>& vector, std::vector<V>& find)
            {
                int occ = 0;
                int potentialIndex = -1;
                bool startedSearch = false;
                if (find.size() < vector.size())
                {
                    for (int i = 0; i < vector.size(); i++)
                    {
                        if (find[occ] == vector[i])
                        {
                            if (!startedSearch)
                            {
                                potentialIndex = i;
                                startedSearch = true;
                            }
                            occ++;
                        }
                        else if (startedSearch && find[occ] == vector[i])
                        {
                            startedSearch = false;
                            occ = 0;
                            potentialIndex = -1;
                        }
                    }
                }
                return potentialIndex;
            }

            template <typename V>
            std::vector<V> getSubVector(const std::vector<V>& vector, int start, int end)
            {
                auto first = vector.begin() + start;
                auto last = vector.end() - end;
                std::vector<V> newVec(first, last);
                return newVec;
            }
        }
    }
}