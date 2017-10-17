#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

namespace obe
{
    namespace System
    {
        enum class WindowContext
        {
            GameWindow,
            EditorWindow
        };

        extern sf::RenderWindow MainWindow;

        void InitWindow(WindowContext context);
        void setTitle(const std::string& title);
        void setSize(unsigned int width, unsigned int height);
    }
}