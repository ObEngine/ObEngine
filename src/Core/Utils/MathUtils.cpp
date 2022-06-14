#include <cmath>
#include <random>

#include <Utils/MathUtils.hpp>

namespace obe::Utils::Math
{
    std::random_device rd;
    std::mt19937 rng { rd() };

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

    bool is_double_int(const double& value)
    {
        return (int(value) == value);
    }

    double convert_to_radian(const double value)
    {
        return (Utils::Math::pi / 180.0) * value;
    }

    double convert_to_degrees(const double value)
    {
        return (180.0 / Utils::Math::pi) * value;
    }

    double normalize(const double value, const double start, const double end)
    {
        const double width = end - start;
        const double offset_value = value - start;

        return (offset_value - (floor(offset_value / width) * width)) + start;
    }
} // namespace obe::Utils::Math
