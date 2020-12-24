#pragma once

namespace obe::Transform
{
    /**
     * \brief Struct representing the View used for internal UnitVector
     *        conversions
     */
    struct ViewStruct
    {
        double w = 1;
        double h = 1;
        double x = 0;
        double y = 0;
    };

    /**
     * \brief Struct representing the Screen used for internal UnitVector
     *        conversions
     */
    struct ScreenStruct
    {
        double w;
        double h;
    };
} // namespace obe::Transform