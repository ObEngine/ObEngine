#include <Utils/VectorUtils.hpp>
#include <string>

namespace obe::Utils::Vector
{
    std::string join(
        std::vector<std::string>& vector, std::string sep, int start, int end)
    {
        std::string result;
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
} // namespace obe::Utils::Vector