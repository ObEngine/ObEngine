#pragma once

#include <Types/SmartEnum.hpp>

namespace obe::transform
{
    /**
     * \brief Different Units used to work with elements position / size in the
     * Scene
     */
    enum class Units
    {
        /**
         * \brief ViewPercentage is an Unit used to place / scale an element
         *        using the View.
         *        Example : x = 0.5, y = 0.5 is the middle of the View
         */
        ViewPercentage,
        /**
         * \brief ViewPercentage is an Unit used to place / scale an element
         *        using the pixels of the View.
         *        Example : x = 500, y = 500 is the middle of a 1000x1000 pixels screen
         */
        ViewPixels,
        /**
         * \brief ViewUnits is an Unit used to place / scale an element using
         *        the View.
         *        Example : x = 1, y = 1 is the middle of a 1000x1000
         *        pixels screen. The screen height will ALWAYS be 2 ViewUnits when
         *        the View size is 1, the width will depend on the screen ratio.
         *        The screen width in ViewUnits can be calculated using this formula :
         *        2 * view_size * (Screen.Width / Screen.Height)
         */
        ViewUnits,
        /**
         * \brief ViewPercentage is an Unit used to place / scale an element
         *        using the pixels of the Scene. Example : x = 4000, y = 10000
         */
        ScenePixels,
        /**
         * \brief SceneUnits is an Unit used to place / scale an element using
         *        the Scene. Example : x = 4.5, y = 2.5
         */
        SceneUnits
    };

    using UnitsMeta = types::SmartEnum<Units>;
} // namespace obe::transform
