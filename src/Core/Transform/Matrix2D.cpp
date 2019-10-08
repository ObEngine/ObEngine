#include <Transform/Matrix2D.hpp>

namespace obe::Transform
{

    Matrix2D::Matrix2D(std::array<double, 4> elements)
    {
        m_elements = elements;
    }

    UnitVector Matrix2D::product(UnitVector vector)
    {
        UnitVector result;
        result.x = m_elements[0] * vector.x + m_elements[1] * vector.y;
        result.y = m_elements[2] * vector.x + m_elements[3] * vector.y;
        return result;
    }
} // namespace obe::Transform