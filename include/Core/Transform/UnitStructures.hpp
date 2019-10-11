#pragma once

namespace obe::Transform
{
    /**
     * \brief Struct representing the View used for internal UnitVector
     * conversions
     */
    struct ViewStruct
    {
        double w;
        double h;
        double x;
        double y;
    };

    /**
     * \brief Struct representing the Screen used for internal UnitVector
     * conversions
     */
    struct ScreenStruct
    {
        double w;
        double h;
    };
} // namespace obe::Transform