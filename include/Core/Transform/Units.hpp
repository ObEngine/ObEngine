#pragma once

#include <string>

namespace obe::Transform
{
    /**
     * \brief Different Units used to work with elements position / size in the
     * Scene
     */
    enum class Units
    {
        /**
         * \brief ViewPercentage is an Unit used to place / scale an element
         * using the View. \n Exemple : x = 0.5, y = 0.5 is the middle of the
         * View
         */
        ViewPercentage,
        /**
         * \brief ViewPercentage is an Unit used to place / scale an element
         * using the pixels of the View. \n Exemple : x = 500, y = 500 is the
         * middle of a 1000x1000 pixels screen
         */
        ViewPixels,
        /**
         * \brief ViewUnits is an Unit used to place / scale an element using
         * the View. \n Exemple : x = 1, y = 1 is the middle of a 1000x1000
         * pixels screen. \n The screen height will ALWAYS be 2 ViewUnits when
         * the View size is 1, the width will depend on the screen ratio. \n The
         * screen width in ViewUnits can be calculated using this formula : 2 *
         * viewSize * (Screen.Width / Screen.Height)
         */
        ViewUnits,
        /**
         * \brief ViewPercentage is an Unit used to place / scale an element
         * using the pixels of the Scene. \n Exemple : x = 4000, y = 10000
         */
        ScenePixels,
        /**
         * \brief SceneUnits is an Unit used to place / scale an element using
         * the Scene. \n Exemple : x = 4.5, y = 2.5
         */
        SceneUnits
    };

    /**
     * \brief Converts a std::string to an Unit
     * \param unit Unit in string form
     * \return The convert Units enum value
     */
    Units stringToUnits(const std::string& unit);
    /**
     * \brief Converts an Unit to a std::string
     * \param unit The Units enum value you want to convert into a std::string
     * \return A std::string containing the Units enum value in string form
     */
    std::string unitsToString(Units unit);
} // namespace obe::Transform