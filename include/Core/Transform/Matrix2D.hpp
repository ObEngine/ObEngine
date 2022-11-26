#pragma once

#include <array>

#include <Transform/Vector2.hpp>

namespace obe::transform
{
    class Matrix2D
    {
    private:
        std::array<double, 4> m_elements;

    public:
        Matrix2D(std::array<double, 4> elements);
        Vector2 product(Vector2 vector);
    };
} // namespace obe::transform
