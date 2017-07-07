#include <Utils/VectorUtils.hpp>

namespace obe
{
    namespace Utils
    {
        namespace Vector
        {
            std::string join(std::vector<std::string>& vector, std::string sep, int start, int end)
            {
                std::string result = "";
                if (end >= vector.size())
                    end = vector.size();
                if (start >= vector.size() - 1)
                    start = vector.size() - 1;
                for (int i = start; i < vector.size() - end; i++)
                {
                    if (i != vector.size() - 1)
                        result += vector[i] + sep;
                    else
                        result += vector[i];
                }
                return result;
            }

            void joinBetween(std::vector<std::string>& vector, std::string joinValue, std::string sep)
            {
                std::string stack = "";
                bool stacking = false;
                std::vector<int> toErase;
                for (int i = 0; i < vector.size(); i++)
                {
                    if (vector.at(i) == joinValue)
                    {
                        if (stacking)
                        {
                            stack += vector.at(i);
                            vector.at(i) = stack;
                            stack = "";
                        }
                        stacking = !stacking;
                    }
                    if (stacking)
                    {
                        stack += vector.at(i) + sep;
                        toErase.push_back(i);
                    }
                }
                for (int i = toErase.size() - 1; i >= 0; i--)
                    vector.erase(vector.begin() + toErase[i]);
            }

            void mergeNeighboors(std::vector<std::string>& vector, std::string n1, std::string n2, std::string sep, bool strict)
            {
                if (vector.size() > 0)
                {
                    std::vector<int> toErase;
                    for (int i = 0; i < vector.size() - 1; i++)
                    {
                        if (strict)
                        {
                            if (vector.at(i) == n1 && vector.at(i + 1) == n2)
                            {
                                vector.at(i) = vector.at(i) + sep + vector.at(i + 1);
                                toErase.push_back(i + 1);
                            }
                        }
                        else
                        {
                            if ((vector.at(i) == n1 && vector.at(i + 1) == n2) || (vector.at(i) == n2 && vector.at(i + 1) == n1))
                            {
                                vector.at(i) = vector.at(i) + sep + vector.at(i + 1);
                                toErase.push_back(i + 1);
                            }
                        }
                    }
                    for (int i = toErase.size() - 1; i >= 0; i--)
                        vector.erase(vector.begin() + toErase[i]);
                }
            }
        }
    }
}