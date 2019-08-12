#pragma once

#include <Transform/UnitVector.hpp>
#include <array>

namespace obe::Transform
{
    class Matrix2D
    {
    private:
        std::array<double, 4> m_elements;
    public:
        Matrix2D(std::array<double, 4> elements);
        UnitVector product(UnitVector vector);
    };
}
