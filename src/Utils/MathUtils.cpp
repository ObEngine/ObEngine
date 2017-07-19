#include <cmath>
#include <random>

#include <Utils/MathUtils.hpp>

namespace obe
{
    namespace Utils
    {
        namespace Math
        {
            const double pi = 3.14159265359;

            std::random_device rd;
            std::mt19937 rng(rd());

            int randint(const int& min, const int& max)
            {
                std::uniform_int_distribution<int> uni(min, max);
                return uni(rng);
            }

            double randfloat()
            {
                std::uniform_real_distribution<> dis(0, 1);
                return dis(rng);
            }

            bool isDoubleInt(const double& value)
            {
                return (trunc(value) == value);
            }
        }
    }
}
