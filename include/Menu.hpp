#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "Cursor.hpp"
#include "Functions.hpp"
#include "PathResolver.hpp"
#include "MapEditor.hpp"
#include "Game.hpp"
#include "Toolkit.hpp"

namespace obe
{
    namespace Modes
    {
        std::string chooseMapMenu();
        void startDevMenu();
    }
}
