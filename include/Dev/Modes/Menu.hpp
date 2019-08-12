#pragma once

#include <string>

/**
* \brief Different Modes or Menus that ObEngine can launch
*/
namespace obe::Modes
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