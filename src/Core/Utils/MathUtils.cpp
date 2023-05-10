#include <cmath>
#include <random>

#include <Utils/MathUtils.hpp>

namespace obe::utils::math
{
    pcg_extras::seed_seq_from<std::random_device> seed_source;
    pcg64 rng(seed_source);

    bool randbool()
    {
        return randfloat() >= 0.5;
    }

    double randfloat()
    {
        // do not put const, might fail depending on libc++
        std::uniform_real_distribution<> dis(0, 1);
        return dis(rng);
    }

    bool is_double_int(const double& value)
    {
        return (static_cast<int>(value) == value);
    }

    double convert_to_radian(const double value)
    {
        return (utils::math::pi / 180.0) * value;
    }

    double convert_to_degrees(const double value)
    {
        return (180.0 / utils::math::pi) * value;
    }

    double normalize(const double value, const double start, const double end)
    {
        const double width = end - start;
        const double offset_value = value - start;

        return (offset_value - (floor(offset_value / width) * width)) + start;
    }
} // namespace obe::utils::math
