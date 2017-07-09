#pragma once

#include <string>

namespace obe
{
    namespace Modes
    {
        /**
         * \brief Starts the menu used to chose a map to edit.
         * \return The path to the chosen map.
         */
        std::string chooseMapMenu();
        /**
         * \brief Starts the development Menu where you can starts other menus from.
         */
        void startDevMenu();
    }
}
