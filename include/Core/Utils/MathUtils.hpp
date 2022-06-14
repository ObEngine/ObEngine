#pragma once

/**
 * \brief Functions to work with maths
 */
namespace obe::Utils::Math
{
    constexpr static double pi = 3.14159265359;

    /**
     * \brief Get a random integer between the given bound
     * \param min Min bound
     * \param max Max bound
     * \return A random int between the given bound
     */
    int randint(const int& min, const int& max);
    /**
     * \brief Get a random double
     * \return A random double between 0.0 and 1.0
     */
    double randfloat();
    /**
     * \brief Get the lowest value between the two given values
     * \tparam N Type of both values
     * \param min1 First value to check
     * \param min2 Second value to check
     * \return The lowest value
     * \thints
     * \thint{get_min, N=$numerics}
     * \endthints
     */
    template <typename N>
    N get_min(const N& min1, const N& min2);
    /**
     * \brief Get the highest value between the two given values
     * \tparam N Type of both values
     * \param max1 First value to check
     * \param max2 Second value to check
     * \return The highest value
     * \thints
     * \thint{get_max, N=$numerics}
     * \endthints
     */
    template <typename N>
    N get_max(const N& max1, const N& max2);
    /**
     * \brief Check if the given value is between the lower bound and the upper
     *        bound
     * \tparam N Type of the value to check
     * \tparam N1 Type of the lower bound
     * \tparam N2 Type of the upper bound
     * \param target Value to check
     * \param lower_bound Lower bound
     * \param upper_bound Upper bound
     * \return true if the value is between the given bound, false otherwise
     * \thints
     * \thint{is_between, N=$numerics;N1=$numerics;N2=$numerics}
     * \endthints
     */
    template <typename N, typename N1, typename N2>
    bool is_between(const N& target, const N1& lower_bound, const N2& upper_bound);
    /**
     * \brief Check if a double is an integer (3.0 for example is equal to 3)
     * \param value Value to check
     * \return true if the double is an integer, false otherwise
     */
    bool is_double_int(const double& value);
    /**
     * \brief Get the sign of the given number
     * \tparam T Type of the value to check
     * \param val Value to check the sign
     * \return -1 if negative, 0 if equal to 0, 1 if positive
     * \thints
     * \thint{sign, T=$numerics}
     * \endthints
     */
    template <typename T>
    int sign(T val);

    /**
     * \brief Converts a degrees angle to radians
     * \param value Angle in degrees
     * \return A double containing the converted value
     */
    double convert_to_radian(double value);
    /**
     * \brief Converts a radians angle to degrees
     * \param value Angle in  radians
     * \return A double containing the converted value
     */
    double convert_to_degrees(double value);
    /**
     * \brief Normalizes a value between start and end
     * \param value Value to normalize
     * \param start Lower bound
     * \param end Higher bound
     * \return Normalized value
     *
     * \paramrename{start,low}
     * \paramrename{end,high}
     */
    double normalize(double value, double start, double end);

    template <typename N>
    N get_min(const N& min1, const N& min2)
    {
        return (min1 < min2) ? min1 : min2;
    }

    template <typename N>
    N get_max(const N& max1, const N& max2)
    {
        return (max1 > max2) ? max1 : max2;
    }

    template <typename N, typename N1, typename N2>
    bool is_between(const N& target, const N1& lower_bound, const N2& upper_bound)
    {
        if (target >= lower_bound && target <= upper_bound)
            return true;
        return false;
    }

    template <typename T>
    int sign(T val)
    {
        return (T(0) < val) - (val < T(0));
    }
} // namespace obe::Utils::Math
