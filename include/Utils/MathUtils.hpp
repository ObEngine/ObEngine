#pragma once

namespace obe
{
    namespace Utils
    {
        namespace Math
        {
            extern const double pi;
            
            int randint(const int& min, const int& max);
            double randfloat();
            template <typename N>
            N getMin(const N& min1, const N& min2);
            template <typename N>
            N getMax(const N& max1, const N& max2);
            template <typename N, typename N1, typename N2>
            bool isBetween(const N& target, const N1& lowerBound, const N2& upperBound);
            bool isDoubleInt(const double& value);
            template <typename T> 
            int sign(T val);

            template <typename N>
            N getMin(const N& min1, const N& min2)
            {
                return (min1 < min2) ? min1 : min2;
            }

            template <typename N>
            N getMax(const N& max1, const N& max2)
            {
                return (max1 > max2) ? max1 : max2;
            }

            template <typename N, typename N1, typename N2>
            bool isBetween(const N& target, const N1& lowerBound, const N2& upperBound)
            {
                if (target >= lowerBound && target <= upperBound)
                    return true;
                return false;
            }

            template <typename T> 
            int sign(T val)
            {
                return (T(0) < val) - (val < T(0));
            }

        }
    }
}