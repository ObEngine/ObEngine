#include <cmath>
#include <random>

#include <Utils/MathUtils.hpp>

namespace obe::Utils::Math
{
    std::random_device rd;
    std::mt19937 rng{ rd() };

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
        return (int(value) == value);
    }

    double convertToRadian(const double value)
    {
        return (Utils::Math::pi / 180.0) * value;
    }

    double convertToDegree(const double value)
    {
        return (180.0 / Utils::Math::pi) * value;
    }

    double normalise(const double value, const double start, const double end)
    {
        const double width = end - start;
        const double offsetValue = value - start;

        return (offsetValue - (floor(offsetValue / width) * width)) + start;
    }
} // namespace obe::Utils::Math